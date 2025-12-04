/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static int	add_operator_token(t_lexer *lex)
{
	t_token_type	type;
	int				len;
	char			*value;
	t_token			*token;

	type = get_operator_type(&lex->input[lex->pos], &len);
	value = ft_substr(lex->input, lex->pos, len);
	if (!value)
		return (0);
	token = token_create(type, value);
	free(value);
	if (!token)
		return (0);
	token_add_back(&lex->tokens, token);
	lex->pos += len;
	return (1);
}

static int	add_word_token(t_lexer *lex)
{
	char	*word;
	t_token	*token;

	word = extract_word(lex);
	if (!word)
		return (0);
	if (*word)
	{
		token = token_create(TOKEN_WORD, word);
		if (!token)
		{
			free(word);
			return (0);
		}
		token_add_back(&lex->tokens, token);
	}
	free(word);
	return (1);
}

static int	is_fd_redir_start(t_lexer *lex)
{
	int		i;
	char	*str;

	str = &lex->input[lex->pos];
	i = 0;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}

static int	tokenize_loop(t_lexer *lex)
{
	while (lex->input[lex->pos])
	{
		skip_whitespace(lex);
		if (!lex->input[lex->pos])
			break ;
		if (lex->quote == QUOTE_NONE && (is_operator_char(lex->input[lex->pos])
				|| is_fd_redir_start(lex)))
		{
			if (!add_operator_token(lex))
				return (0);
		}
		else
		{
			if (!add_word_token(lex))
				return (0);
		}
	}
	return (1);
}

t_token	*lexer_tokenize(char *input)
{
	t_lexer	lex;

	lex.input = input;
	lex.pos = 0;
	lex.quote = QUOTE_NONE;
	lex.tokens = NULL;
	if (!tokenize_loop(&lex))
	{
		token_list_free(lex.tokens);
		print_quote_error(lex.quote);
		return (NULL);
	}
	if (lex.quote != QUOTE_NONE)
	{
		print_quote_error(lex.quote);
		token_list_free(lex.tokens);
		return (NULL);
	}
	return (lex.tokens);
}
