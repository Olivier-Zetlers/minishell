/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

t_cmd	*cmd_create(void)
{
	t_cmd	*cmd;

	cmd = safe_malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	return (cmd);
}

void	cmd_add_back(t_cmd **list, t_cmd *new)
{
	t_cmd	*last;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	redir_list_free(t_redir *redirects)
{
	t_redir	*tmp;

	while (redirects)
	{
		tmp = redirects->next;
		if (redirects->file)
			free(redirects->file);
		if (redirects->heredoc_fd != -1)
			close(redirects->heredoc_fd);
		free(redirects);
		redirects = tmp;
	}
}

void	cmd_list_free(t_cmd *commands)
{
	t_cmd	*tmp;

	while (commands)
	{
		tmp = commands->next;
		if (commands->argv)
			ft_free_array(commands->argv);
		if (commands->redirects)
			redir_list_free(commands->redirects);
		free(commands);
		commands = tmp;
	}
}
