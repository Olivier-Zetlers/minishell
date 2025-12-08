/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/12/08 19:53:38 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	setup_pipes(t_cmd *cmd, t_cmd *prev)
{
	t_cmd	*current;

	(void)prev;
	current = cmd;
	while (current && current->next)
	{
		if (pipe(current->pipe_fd) == -1)
		{
			close_all_pipes(cmd);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	setup_child_pipes(t_cmd *cmd, t_cmd *all_cmds)
{
	t_cmd	*prev;

	prev = NULL;
	while (all_cmds && all_cmds != cmd)
	{
		prev = all_cmds;
		all_cmds = all_cmds->next;
	}
	if (prev && prev->pipe_fd[0] != -1)
	{
		if (dup2(prev->pipe_fd[0], STDIN_FILENO) == -1)
			return (0);
	}
	if (cmd->next && cmd->pipe_fd[1] != -1)
	{
		if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			return (0);
	}
	return (1);
}
