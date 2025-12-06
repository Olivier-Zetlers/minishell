/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "expander.h"
#include "utils.h"

/* OLD VERSION
static t_token	*extract_until_semicolon(t_token **tokens)
{
	t_token	*head;
	t_token	*tail;
	t_token	*next;

	head = NULL;
	tail = NULL;
	while (*tokens && (*tokens)->type != TOKEN_SEMICOLON)
	{
		next = (*tokens)->next;
		(*tokens)->next = NULL;
		if (!head)
			head = *tokens;
		else
			tail->next = *tokens;
		tail = *tokens;
		*tokens = next;
	}
	if (*tokens && (*tokens)->type == TOKEN_SEMICOLON)
		*tokens = (*tokens)->next;
	return (head);
}

static void	execute_all_sequences(t_shell *shell, t_token *tokens)
{
	t_token	*seq_tokens;
	t_cmd	*commands;

	while (tokens)
	{
		seq_tokens = extract_until_semicolon(&tokens);
		if (!seq_tokens)
			continue ;
		commands = parser_parse(seq_tokens);
		token_list_free(seq_tokens);
		if (commands)
		{
			if (process_all_heredocs(shell, commands) == -1)
			{
				cmd_list_free(commands);
				continue ;
			}
			expand_commands(shell, commands);
			shell->last_status = executor_run(shell, commands);
			cmd_list_free(commands);
		}
	}
}
*/

static void	execute_all_sequences(t_shell *shell, t_token *tokens)
{
	t_cmd	*commands;

	if (!tokens)
		return ;
	commands = parser_parse(tokens);
	token_list_free(tokens);
	if (!commands)
		return ;
	if (process_all_heredocs(shell, commands) == -1)
	{
		cmd_list_free(commands);
		return ;
	}
	expand_commands(shell, commands);
	shell->last_status = executor_run(shell, commands);
	cmd_list_free(commands);
}

void	shell_execute_line(t_shell *shell, char *line)
{
	t_token	*tokens;

	tokens = lexer_tokenize(line);
	if (!tokens)
	{
		shell->last_status = 2;
		return ;
	}
	if (!parser_check_syntax(tokens))
	{
		shell->last_status = 2;
		token_list_free(tokens);
		return ;
	}
	execute_all_sequences(shell, tokens);
}

static void	process_line(t_shell *shell, char *line)
{
	if (g_sig == SIGINT)
	{
		shell->last_status = 130;
		g_sig = 0;
	}
	if (shell->interactive)
		add_history(line);
	shell_execute_line(shell, line);
	free(line);
}

void	shell_loop(t_shell *shell)
{
	char	*line;

	init_shell_signals(shell);
	while (shell->running)
	{
		if (shell->interactive)
		{
			line = readline(PROMPT);
		}
		else
			line = read_line_noninteractive();
		if (!line)
		{
			if (shell->interactive)
				write(2, "exit\n", 5);
			shell->running = 0;
			break ;
		}
		if (*line)
			process_line(shell, line);
		else
			free(line);
	}
}
