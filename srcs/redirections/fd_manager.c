/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	close_fd_if_valid(int fd)
{
	if (fd >= 0)
	{
		if (close(fd) == -1 && errno != EBADF)
			perror("minishell: close warning");
	}
}

void	cleanup_cmd_fds(t_cmd *cmd)
{
	close_fd_if_valid(cmd->pipe_fd[0]);
	close_fd_if_valid(cmd->pipe_fd[1]);
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
}

int	dup_and_close(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		return (-1);
	if (close(oldfd) == -1 && errno != EBADF)
		perror("minishell: close warning");
	return (0);
}
