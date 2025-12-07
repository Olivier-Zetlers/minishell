/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <readline/readline.h>
#include <termios.h>

void	signal_handler(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
	{
		write(2, "^C\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signals(t_sig_mode mode)
{
	if (mode == SIG_INTERACTIVE)
		setup_interactive_signals();
	else if (mode == SIG_CHILD)
		setup_child_signals();
	else if (mode == SIG_EXECUTING)
		setup_executing_signals();
	else if (mode == SIG_HEREDOC)
		setup_heredoc_signals();
}

void	handle_signal_status(t_shell *shell, int status)
{
	if (WIFSIGNALED(status))
	{
		shell->last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
	}
}
