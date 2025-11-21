/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* Parser context */
typedef struct s_parser
{
	t_token		*current;
	t_cmd		*commands;
	int			error;
}	t_parser;

/* Parser function prototypes */
t_cmd		*parser_parse(t_token *tokens);
int			parser_check_syntax(t_token *tokens);
t_cmd		*cmd_create(void);
void		cmd_add_back(t_cmd **list, t_cmd *new);
void		cmd_list_free(t_cmd *commands);
int			cmd_add_arg(t_cmd *cmd, char *arg);
int			parse_redirections(t_parser *parser, t_cmd *cmd);
t_redir		*redir_create(t_redir_type type, char *file, int fd);
void		redir_add_back(t_redir **list, t_redir *new);
void		redir_list_free(t_redir *redirects);

#endif
