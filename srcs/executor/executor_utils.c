/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <sys/stat.h>

void	save_standard_fds(int saved_fds[3])
{
	saved_fds[0] = dup(STDIN_FILENO);
	if (saved_fds[0] == -1)
		perror("minishell: dup");
	saved_fds[1] = dup(STDOUT_FILENO);
	if (saved_fds[1] == -1)
		perror("minishell: dup");
	saved_fds[2] = dup(STDERR_FILENO);
	if (saved_fds[2] == -1)
		perror("minishell: dup");
}

void	restore_standard_fds(int saved_fds[3])
{
	if (dup2(saved_fds[0], STDIN_FILENO) == -1)
		perror("minishell: dup2");
	if (dup2(saved_fds[1], STDOUT_FILENO) == -1)
		perror("minishell: dup2");
	if (dup2(saved_fds[2], STDERR_FILENO) == -1)
		perror("minishell: dup2");
	if (close(saved_fds[0]) == -1 && errno != EBADF)
		perror("minishell: close warning");
	if (close(saved_fds[1]) == -1 && errno != EBADF)
		perror("minishell: close warning");
	if (close(saved_fds[2]) == -1 && errno != EBADF)
		perror("minishell: close warning");
}

void	close_all_pipes(t_cmd *commands)
{
	t_cmd	*current;

	current = commands;
	while (current)
	{
		if (current->pipe_fd[0] != -1)
		{
			if (close(current->pipe_fd[0]) == -1 && errno != EBADF)
				perror("minishell: close warning");
		}
		if (current->pipe_fd[1] != -1)
		{
			if (close(current->pipe_fd[1]) == -1 && errno != EBADF)
				perror("minishell: close warning");
		}
		current = current->next;
	}
}

static int	do_wait(pid_t pid)
{
	int	status;
	int	result;

	result = waitpid(pid, &status, 0);
	while (result == -1 && errno == EINTR)
		result = waitpid(pid, &status, 0);
	if (result == -1)
		return (-1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	wait_for_children(int *pids, int count)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < count)
	{
		if (pids[i] == -127 && i == count - 1)
			result = 127;
		else if (pids[i] != -127 && i == count - 1)
			result = do_wait(pids[i]);
		else if (pids[i] != -127)
			do_wait(pids[i]);
		i++;
	}
	return (result);
}
