/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

int	handle_quotes(t_lexer *lex, char quote_char)
{
	if (lex->quote == QUOTE_NONE)
	{
		if (quote_char == '\'')
			lex->quote = QUOTE_SINGLE;
		else if (quote_char == '"')
			lex->quote = QUOTE_DOUBLE;
		return (1);
	}
	else if ((lex->quote == QUOTE_SINGLE && quote_char == '\'')
		|| (lex->quote == QUOTE_DOUBLE && quote_char == '"'))
	{
		lex->quote = QUOTE_NONE;
		return (1);
	}
	return (0);
}

static int	should_break_word(t_lexer *lex, char c)
{
	if (lex->quote != QUOTE_NONE)
		return (0);
	if (ft_isspace(c))
		return (1);
	if (is_operator_char(c))
		return (1);
	return (0);
}

static int	append_to_word(char **word, size_t *size, size_t *cap, char c)
{
	char	*new_word;

	if (*size >= *cap - 1)
	{
		*cap *= 2;
		new_word = realloc(*word, *cap);
		if (!new_word)
		{
			free(*word);
			*word = NULL;
			return (0);
		}
		*word = new_word;
	}
	(*word)[*size] = c;
	(*size)++;
	return (1);
}

static int	process_char_dyn(t_lexer *lex, char **w, size_t *s, size_t *c)
{
	char	ch;

	ch = lex->input[lex->pos];
	if (ch == '\'' || ch == '"')
		handle_quotes(lex, ch);
	if (!append_to_word(w, s, c, ch))
		return (0);
	lex->pos++;
	return (1);
}

char	*extract_word(t_lexer *lex)
{
	char	*word;
	char	*result;
	size_t	size;
	size_t	capacity;

	capacity = 128;
	word = malloc(capacity);
	if (!word)
		return (NULL);
	size = 0;
	while (lex->input[lex->pos])
	{
		if (should_break_word(lex, lex->input[lex->pos]))
			break ;
		if (!process_char_dyn(lex, &word, &size, &capacity))
			return (NULL);
	}
	word[size] = '\0';
	result = ft_strdup(word);
	free(word);
	return (result);
}
