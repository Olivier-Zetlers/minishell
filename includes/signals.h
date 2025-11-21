/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"
# include <signal.h>

/* Signal handling modes */
typedef enum e_sig_mode
{
	SIG_INTERACTIVE,
	SIG_EXECUTING,
	SIG_HEREDOC,
	SIG_CHILD
}	t_sig_mode;

/* Signal function prototypes */
void	setup_signals(t_sig_mode mode);
void	setup_heredoc_signals(void);
void	setup_interactive_signals(void);
void	setup_child_signals(void);
void	setup_executing_signals(void);
void	signal_handler(int sig);
void	handle_signal_status(t_shell *shell, int status);

#endif
