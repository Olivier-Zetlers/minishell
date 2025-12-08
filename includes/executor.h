/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <termios.h>

/* Heredoc context structure */
typedef struct s_heredoc
{
	int				pipefd[2];
	struct termios	saved_term;
	int				term_saved;
}	t_heredoc;

/* Executor function prototypes */
int		executor_run(t_shell *shell, t_cmd *commands);
int		execute_single_cmd(t_shell *shell, t_cmd *cmd);
int		execute_pipeline(t_shell *shell, t_cmd *commands);
char	*resolve_path(char *cmd, t_env *env);
int		setup_redirections(t_redir *redirects);
int		setup_pipes(t_cmd *cmd, t_cmd *prev);
int		setup_child_pipes(t_cmd *cmd, t_cmd *all_cmds);
void	close_all_pipes(t_cmd *commands);
int		wait_for_children(int *pids, int count);
int		wait_for_child(t_shell *shell, pid_t pid);
int		fork_empty_command(t_cmd *cmd, t_cmd *all_cmds);
void	restore_standard_fds(int saved_fds[3]);
void	save_standard_fds(int saved_fds[3]);
int		handle_path_error(t_shell *shell, char *cmd);
int		execute_redirections_only(t_cmd *cmd);
int		execute_single_builtin(t_shell *shell, t_cmd *cmd);


/* Path resolver helpers */
int		report_not_found(const char *cmd);
int		report_isdir(const char *cmd);
int		report_cmdnf(const char *cmd);
int		try_exec_no_search(char **argv, char **envp);
int		is_directory(const char *p);

/* Redirection utilities */
int		process_heredoc(t_shell *shell, t_redir *redir);
int		has_heredoc(t_redir *redirects);
int		process_all_heredocs(t_shell *shell, t_cmd *commands);
int		should_expand_heredoc(char *delimiter);
void	cleanup_cmd_fds(t_cmd *cmd);
int		dup_and_close(int oldfd, int newfd);

/* Heredoc helpers */
int		init_heredoc(t_shell *shell, t_heredoc *context);
void	wait_heredoc_child(pid_t pid, int *status);
void	restore_heredoc_state(t_shell *shell, t_heredoc *context);
int		handle_heredoc_sigint(t_shell *shell, t_heredoc *context);

#endif
