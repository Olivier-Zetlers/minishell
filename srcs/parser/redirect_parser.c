/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

t_redir	*redir_create(t_redir_type type, char *file, int fd)
{
	t_redir	*redir;

	redir = safe_malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->fd = fd;
	redir->heredoc_fd = -1;
	redir->next = NULL;
	return (redir);
}

void	redir_add_back(t_redir **list, t_redir *new)
{
	t_redir	*last;

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

static t_redir_type	token_to_redir_type(t_token_type type)
{
	if (type == TOKEN_LESS)
		return (REDIR_INPUT);
	else if (type == TOKEN_GREAT)
		return (REDIR_OUTPUT);
	else if (type == TOKEN_DGREAT)
		return (REDIR_APPEND);
	else if (type == TOKEN_DLESS)
		return (REDIR_HEREDOC);
	return (REDIR_INPUT);
}

static int	parse_fd_from_token(char *value, t_redir_type type)
{
	int	fd;
	int	i;

	i = 0;
	while (value[i] && ft_isdigit(value[i]))
		i++;
	if (i == 0)
	{
		if (type == REDIR_INPUT || type == REDIR_HEREDOC)
			return (0);
		else
			return (1);
	}
	fd = ft_atoi(value);
	return (fd);
}

int	parse_redirections(t_parser *parser, t_cmd *cmd)
{
	t_redir_type	type;
	t_redir			*redir;
	int				fd;

	type = token_to_redir_type(parser->current->type);
	fd = parse_fd_from_token(parser->current->value, type);
	parser->current = parser->current->next;
	if (!parser->current)
	{
		syntax_error("newline");
		parser->error = 1;
		return (0);
	}
	if (parser->current->type != TOKEN_WORD)
	{
		syntax_error(parser->current->value);
		parser->error = 1;
		return (0);
	}
	redir = redir_create(type, parser->current->value, fd);
	if (!redir)
		return (0);
	redir_add_back(&cmd->redirects, redir);
	parser->current = parser->current->next;
	return (1);
}
