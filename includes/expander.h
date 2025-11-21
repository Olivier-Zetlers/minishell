/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/* Expansion context */
typedef struct s_expand
{
	char			*input;
	char			*result;
	int				pos;
	int				in_double;
	t_shell			*shell;
}	t_expand;

/* Expander function prototypes */
void	expand_commands(t_shell *shell, t_cmd *commands);
char	*expand_string(t_shell *shell, char *str);
char	*expand_variable(t_shell *shell, char *var_name);
char	*remove_quotes(char *str);
int		needs_expansion(char *str);
int		is_valid_var_char(char c, int first);
char	*extract_var_name(char *str, int *len);
char	**split_on_whitespace(char *str);
int		has_quotes(char *str);

/* Argv expansion helpers */
int		count_argv(char **argv);
void	free_argv(char **argv);
char	**create_single_field(char *str);
char	**expand_and_split_token(t_shell *shell, char *token);
void	populate_new_argv(t_shell *shell, char **old, char **new);
int		check_ambiguous_redirect(char *original, char **fields);

#endif
