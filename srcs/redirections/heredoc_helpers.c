/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "signals.h"

int	init_heredoc(t_shell *shell, t_heredoc *ctx)
{
	if (pipe(ctx->pipefd) == -1)
		return (-1);
	shell->in_heredoc = 1;
	ctx->term_saved = 0;
	if (shell->interactive && isatty(STDIN_FILENO))
		ctx->term_saved = (tcgetattr(STDIN_FILENO, &ctx->saved_term) == 0);
	setup_signals(SIG_EXECUTING);
	return (0);
}

void	wait_heredoc_child(pid_t pid, int *status)
{
	int	result;

	result = waitpid(pid, status, 0);
	while (result == -1 && errno == EINTR)
		result = waitpid(pid, status, 0);
}

void	restore_heredoc_state(t_shell *shell, t_heredoc *ctx)
{
	shell->in_heredoc = 0;
	if (ctx->term_saved)
		tcsetattr(STDIN_FILENO, TCSANOW, &ctx->saved_term);
	if (shell->interactive)
		setup_signals(SIG_INTERACTIVE);
}

int	handle_heredoc_sigint(t_shell *shell, t_heredoc *ctx)
{
	if (close(ctx->pipefd[0]) == -1 && errno != EBADF)
		perror("minishell: close warning");
	write(1, "^C\n", 3);
	shell->last_status = 130;
	return (-1);
}
