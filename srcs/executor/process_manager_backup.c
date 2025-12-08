/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/12/08 19:54:31 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "signals.h"
#include "utils.h"

static int	execute_child_builtin(t_shell *shell, t_cmd *cmd, t_cmd *all_cmds)
{
	int	status;

	setup_signals(SIG_CHILD);
	setup_child_pipes(cmd, all_cmds);
	if (setup_redirections(cmd->redirects) == -1)
		exit(1);
	close_all_pipes(all_cmds);
	status = execute_builtin(shell, cmd->argv);
	exit(status);
}

static void	execute_child(t_shell *shell, t_cmd *cmd, char *path, t_cmd *all)
{
	char	**envp;
	int		status;

	setup_signals(SIG_CHILD);
	setup_child_pipes(cmd, all);
	if (setup_redirections(cmd->redirects) == -1)
		exit(1);
	close_all_pipes(all);
	envp = env_to_array(shell->env);
	if (!envp)
		exit(1);
	if (!path && !ft_strchr(cmd->argv[0], '/'))
	{
		status = try_exec_no_search(cmd->argv, envp);
		ft_free_array(envp);
		exit(status);
	}
	execve(path, cmd->argv, envp);
	print_errno_error(cmd->argv[0], NULL);
	ft_free_array(envp);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

static int	fork_process(t_shell *shell, t_cmd *cmd, t_cmd *all_cmds)
{
	pid_t	pid;
	char	*path;
	char	*penv;

	if (!cmd->argv || !cmd->argv[0])
		return (fork_empty_command(cmd, all_cmds));
	penv = env_get(shell->env, "PATH");
	if (is_builtin(cmd->argv[0]) && ((penv && *penv)
			|| ft_strncmp(cmd->argv[0], "env", 4) != 0))
	{
		pid = fork();
		if (pid == 0)
			execute_child_builtin(shell, cmd, all_cmds);
		return (pid);
	}
	path = resolve_path(cmd->argv[0], shell->env);
	pid = fork();
	if (pid == 0)
		execute_child(shell, cmd, path, all_cmds);
	return (free(path), pid);
}

static int	fork_all(t_shell *shell, t_cmd *commands, int *pids, int count)
{
	int		i;
	t_cmd	*current;

	current = commands;
	i = 0;
	while (current && i < count)
	{
		pids[i] = fork_process(shell, current, commands);
		if (pids[i] < 0 && pids[i] != -127)
			return (1);
		current = current->next;
		i++;
	}
	return (0);
}

int	execute_pipeline(t_shell *shell, t_cmd *commands)
{
	int		*pids;
	int		count;
	t_cmd	*current;

	count = 0;
	current = commands;
	while (current && ++count)
		current = current->next;

	pids = safe_malloc(sizeof(int) * count);
	if (!pids)
		return (1);

	// Set up pipes and handle failure
	if (!setup_pipes(commands, NULL))
	{
		close_all_pipes(commands);  // Ensure pipes are closed on failure
		free(pids);
		return (1);
	}

	// Handle fork failure
	if (fork_all(shell, commands, pids, count) != 0)
	{
		close_all_pipes(commands);  // Ensure pipes are closed on failure
		free(pids);
		return (1);
	}

	// Success case, close pipes and handle execution
	close_all_pipes(commands);
	setup_signals(SIG_EXECUTING);
	shell->last_status = wait_for_children(pids, count);
	if (shell->interactive)
		setup_signals(SIG_INTERACTIVE);
	if (shell->last_status == 130)
		write(1, "\n", 1);
	else if (shell->last_status == 131)
		write(2, "Quit (core dumped)\n", 19);
	free(pids);
	return (shell->last_status);
}

