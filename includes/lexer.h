/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/* Quote state tracking */
typedef enum e_quote_state
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_state;

/* Lexer context structure */
typedef struct s_lexer
{
	char			*input;
	int				pos;
	t_quote_state	quote;
	t_token			*tokens;
}	t_lexer;

/* Lexer function prototypes */
t_token			*lexer_tokenize(char *input);
t_token			*token_create(t_token_type type, char *value);
void			token_add_back(t_token **list, t_token *new);
void			token_list_free(t_token *tokens);
int				is_operator_char(char c);
t_token_type	get_operator_type(char *str, int *len);
void			skip_whitespace(t_lexer *lex);
void			print_quote_error(t_quote_state quote);
int				handle_quotes(t_lexer *lex, char quote_char);
char			*extract_word(t_lexer *lex);

#endif
