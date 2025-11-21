/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	should_expand_heredoc(char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

int	has_heredoc(t_redir *redirects)
{
	while (redirects)
	{
		if (redirects->type == REDIR_HEREDOC)
			return (1);
		redirects = redirects->next;
	}
	return (0);
}

int	process_all_heredocs(t_shell *shell, t_cmd *commands)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = commands;
	while (cmd)
	{
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				if (process_heredoc(shell, redir) == -1)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
