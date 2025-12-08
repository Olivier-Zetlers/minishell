/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"
#include "signals.h"
#include "utils.h"
#include <termios.h>

static void	write_heredoc_line(int fd, char *line, t_shell *shell, int expand)
{
	char	*expanded;

	if (expand)
	{
		expanded = expand_string(shell, line);
		if (expanded)
		{
			write(fd, expanded, ft_strlen(expanded));
			free(expanded);
		}
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static int	check_heredoc_line(char *line, char *delim_clean)
{
	int	delim_len;
	int	line_len;

	if (!line || g_sig == SIGINT)
	{
		if (g_sig == SIGINT)
			exit(130);
		return (1);
	}
	delim_len = ft_strlen(delim_clean);
	line_len = ft_strlen(line);
	if (line_len == delim_len
		&& ft_strncmp(line, delim_clean, delim_len) == 0)
		return (1);
	return (0);
}

static char	*read_heredoc_line(int interactive)
{
	char	buf[1024];
	int		i;
	int		c;

	if (interactive)
		return (readline("> "));
	i = 0;
	while (1)
	{
		c = read(STDIN_FILENO, &buf[i], 1);
		if (c <= 0)
			return (NULL);
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			return (ft_strdup(buf));
		}
		i++;
		if (i >= 1023)
		{
			buf[i] = '\0';
			return (ft_strdup(buf));
		}
	}
}

static int	heredoc_child(t_shell *shell, char *delimiter, int write_fd)
{
	char	*line;
	char	*delim_clean;
	int		expand;

	setup_signals(SIG_HEREDOC);
	delim_clean = remove_quotes(delimiter);
	expand = should_expand_heredoc(delimiter);
	while (1)
	{
		line = read_heredoc_line(shell->interactive);
		if (check_heredoc_line(line, delim_clean))
		{
			if (line)
				free(line);
			break ;
		}
		write_heredoc_line(write_fd, line, shell, expand);
		free(line);
	}
	free(delim_clean);
	if (close(write_fd) == -1 && errno != EBADF)
		perror("minishell: close warning");
	exit(0);
}

/*
int	process_heredoc(t_shell *shell, t_redir *redir)
{
	t_heredoc	context;
	pid_t		pid;
	int			status;

	if (init_heredoc(shell, &context) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		heredoc_child(shell, redir->file, context.pipefd[1]);
	if (close(context.pipefd[1]) == -1 && errno != EBADF)
		perror("minishell: close warning");
	wait_heredoc_child(pid, &status);
	restore_heredoc_state(shell, &context);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (handle_heredoc_sigint(shell, &context));
	redir->heredoc_fd = context.pipefd[0];
	return (0);
}
*/

int	process_heredoc(t_shell *shell, t_redir *redir)
{
	t_heredoc	context;
	pid_t		pid;
	int			status;

	if (init_heredoc(shell, &context) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		if (close(context.pipefd[0]) == -1 && errno != EBADF)
			perror("minishell: close warning");
		heredoc_child(shell, redir->file, context.pipefd[1]);
	}
	if (close(context.pipefd[1]) == -1 && errno != EBADF)
		perror("minishell: close warning");
	wait_heredoc_child(pid, &status);
	restore_heredoc_state(shell, &context);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (handle_heredoc_sigint(shell, &context));
	redir->heredoc_fd = context.pipefd[0];
	return (0);
}
