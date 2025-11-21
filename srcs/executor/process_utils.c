/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "signals.h"

int	fork_empty_command(t_cmd *cmd, t_cmd *all_cmds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_child_pipes(cmd, all_cmds);
		if (setup_redirections(cmd->redirects) == -1)
			exit(1);
		close_all_pipes(all_cmds);
		exit(0);
	}
	return (pid);
}

int	wait_for_child(t_shell *shell, pid_t pid)
{
	int	status;
	int	result;

	setup_signals(SIG_EXECUTING);
	result = waitpid(pid, &status, 0);
	while (result == -1 && errno == EINTR)
		result = waitpid(pid, &status, 0);
	if (shell->interactive)
		setup_signals(SIG_INTERACTIVE);
	if (result == -1)
		perror("minishell: waitpid");
	handle_signal_status(shell, status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (shell->last_status);
}
