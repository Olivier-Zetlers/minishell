/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static int	parse_simple_command(t_parser *parser, t_cmd *cmd)
{
	while (parser->current && parser->current->type != TOKEN_PIPE)
	{
		if (parser->current->type >= TOKEN_LESS
			&& parser->current->type <= TOKEN_DLESS)
		{
			if (!parse_redirections(parser, cmd))
				return (0);
		}
		else if (parser->current->type == TOKEN_WORD)
		{
			if (!cmd_add_arg(cmd, parser->current->value))
				return (0);
			parser->current = parser->current->next;
		}
		else
			parser->current = parser->current->next;
	}
	return ((cmd->argv && cmd->argv[0]) || cmd->redirects);
}

static t_cmd	*parse_pipeline(t_parser *parser)
{
	t_cmd	*cmd;
	t_cmd	*head;

	head = NULL;
	while (parser->current && !parser->error)
	{
		cmd = cmd_create();
		if (!cmd)
			return (NULL);
		if (!parse_simple_command(parser, cmd))
		{
			cmd_list_free(cmd);
			cmd_list_free(head);
			return (NULL);
		}
		cmd_add_back(&head, cmd);
		if (parser->current && parser->current->type == TOKEN_PIPE)
			parser->current = parser->current->next;
		else
			break ;
	}
	return (head);
}

t_cmd	*parser_parse(t_token *tokens)
{
	t_parser	parser;
	t_cmd		*commands;

	if (!tokens)
		return (NULL);
	parser.current = tokens;
	parser.error = 0;
	commands = parse_pipeline(&parser);
	if (parser.error)
	{
		cmd_list_free(commands);
		return (NULL);
	}
	return (commands);
}
