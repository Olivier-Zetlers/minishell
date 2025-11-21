/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	skip_whitespace(t_lexer *lex)
{
	while (lex->input[lex->pos] && ft_isspace(lex->input[lex->pos]))
		lex->pos++;
}

void	print_quote_error(t_quote_state quote)
{
	if (quote == QUOTE_SINGLE)
		write(2, "minishell: unexpected EOF while looking "
			"for matching `''\n", 58);
	else if (quote == QUOTE_DOUBLE)
		write(2, "minishell: unexpected EOF while looking "
			"for matching `\"'\n", 58);
}
