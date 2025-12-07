/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

# define PROMPT "minishell$ "
# define ERROR_PREFIX "minishell: "

/* Token types for lexical analysis */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_SEMICOLON,
	TOKEN_LESS,
	TOKEN_GREAT,
	TOKEN_DGREAT,
	TOKEN_DLESS,
	TOKEN_EOF
}	t_token_type;

/* Single global variable as per requirements */
extern volatile sig_atomic_t	g_sig;

/* Token structure for lexer output */
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

/* Redirection types */
typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

/* Redirection node */
typedef struct s_redir
{
	t_redir_type		type;
	char				*file;
	int					fd;
	int					heredoc_fd;
	struct s_redir		*next;
}	t_redir;

/* Command node for execution */
typedef struct s_cmd
{
	char				**argv;
	t_redir				*redirects;
	int					pipe_fd[2];
	struct s_cmd		*next;
}	t_cmd;

/* Environment variable node */
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

/* Main shell structure */
typedef struct s_shell
{
	t_env				*env;
	int					last_status;
	int					running;
	int					interactive;
	int					in_heredoc;
}	t_shell;

/* Core function prototypes */
t_shell	*shell_init(char **envp);
void	init_shell_signals(t_shell *shell);
void	shell_loop(t_shell *shell);
void	shell_cleanup(t_shell *shell);
void	shell_execute_line(t_shell *shell, char *line);
char	*read_line_noninteractive(void);

#endif
