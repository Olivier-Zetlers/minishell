/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/12/08 20:10:04 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "signals.h"
#include "utils.h"

static int	execute_external(t_shell *shell, t_cmd *cmd, char *path)
{
	char	**envp;

	envp = env_to_array(shell->env);
	if (!envp)
		exit(1);
	execve(path, cmd->argv, envp);
	print_errno_error(cmd->argv[0], NULL);
	ft_free_array(envp);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

static void	execute_child_process(t_shell *shell, t_cmd *cmd, char *path)
{
	char	**envp;
	int		status;

	setup_signals(SIG_CHILD);
	if (setup_redirections(cmd->redirects) == -1)
		exit(1);
	if (!path && !ft_strchr(cmd->argv[0], '/'))
	{
		envp = env_to_array(shell->env);
		if (!envp)
			exit(1);
		status = try_exec_no_search(cmd->argv, envp);
		ft_free_array(envp);
		exit(status);
	}
	execute_external(shell, cmd, path);
}

static int	fork_and_execute(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	char	*path;
	char	*path_env;

	path = resolve_path(cmd->argv[0], shell->env);
	if (!path && ft_strchr(cmd->argv[0], '/'))
		return (handle_path_error(shell, cmd->argv[0]));
	if (!path && !ft_strchr(cmd->argv[0], '/'))
	{
		path_env = env_get(shell->env, "PATH");
		if (path_env && *path_env)
			return (handle_path_error(shell, cmd->argv[0]));
	}
	pid = fork();
	if (pid == 0)
		execute_child_process(shell, cmd, path);
	free(path);
	if (pid < 0)
		return (1);
	return (wait_for_child(shell, pid));
}

int	execute_single_cmd(t_shell *shell, t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (!cmd->argv || !cmd->argv[0])
		return (execute_redirections_only(cmd));
	if (is_builtin(cmd->argv[0]))
		return (execute_single_builtin(shell, cmd));
	return (fork_and_execute(shell, cmd));
}

int	executor_run(t_shell *shell, t_cmd *commands)
{
	if (!commands)
		return (0);
	if (!commands->next)
		return (execute_single_cmd(shell, commands));
	else
		return (execute_pipeline(shell, commands));
}

