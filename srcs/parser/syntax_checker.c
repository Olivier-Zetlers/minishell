/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static int	check_pipe_syntax(t_token *token)
{
	if (!token->next)
	{
		syntax_error("newline");
		return (0);
	}
	if (token->next->type == TOKEN_PIPE)
	{
		syntax_error("|");
		return (0);
	}
	if (token->next->type == TOKEN_SEMICOLON)
	{
		syntax_error(";");
		return (0);
	}
	return (1);
}

static int	check_redirect_syntax(t_token *token)
{
	if (!token->next)
	{
		syntax_error("newline");
		return (0);
	}
	if (token->next->type != TOKEN_WORD)
	{
		syntax_error(token->next->value);
		return (0);
	}
	return (1);
}

int	parser_check_syntax(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (1);
	current = tokens;
	if (current->type == TOKEN_PIPE)
	{
		syntax_error("|");
		return (0);
	}
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!check_pipe_syntax(current))
				return (0);
		}
		else if (current->type >= TOKEN_LESS && current->type <= TOKEN_DLESS)
		{
			if (!check_redirect_syntax(current))
				return (0);
		}
		current = current->next;
	}
	return (1);
}
