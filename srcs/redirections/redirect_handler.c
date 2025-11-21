/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"

static int	handle_input_redirect(char *file, int target_fd)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_errno_error(file, NULL);
		return (-1);
	}
	if (dup2(fd, target_fd) == -1)
	{
		if (close(fd) == -1 && errno != EBADF)
			perror("minishell: close warning");
		return (-1);
	}
	if (close(fd) == -1 && errno != EBADF)
		perror("minishell: close warning");
	return (0);
}

static int	handle_output_redirect(char *file, int append, int target_fd)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		print_errno_error(file, NULL);
		return (-1);
	}
	if (dup2(fd, target_fd) == -1)
	{
		if (close(fd) == -1 && errno != EBADF)
			perror("minishell: close warning");
		return (-1);
	}
	if (close(fd) == -1 && errno != EBADF)
		perror("minishell: close warning");
	return (0);
}

static int	handle_single_redirect(t_redir *redir)
{
	if (redir->type == REDIR_INPUT)
		return (handle_input_redirect(redir->file, redir->fd));
	else if (redir->type == REDIR_OUTPUT)
		return (handle_output_redirect(redir->file, 0, redir->fd));
	else if (redir->type == REDIR_APPEND)
		return (handle_output_redirect(redir->file, 1, redir->fd));
	else if (redir->type == REDIR_HEREDOC && redir->heredoc_fd != -1)
	{
		if (dup2(redir->heredoc_fd, redir->fd) == -1)
			return (-1);
		if (close(redir->heredoc_fd) == -1 && errno != EBADF)
			perror("minishell: close warning");
		redir->heredoc_fd = -1;
	}
	return (0);
}

int	setup_redirections(t_redir *redirects)
{
	t_redir	*current;

	current = redirects;
	while (current)
	{
		if (handle_single_redirect(current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}
