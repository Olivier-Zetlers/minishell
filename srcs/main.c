/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "utils.h"

volatile sig_atomic_t	g_sig = 0;

static void	check_interactive_mode(t_shell *shell)
{
	shell->interactive = isatty(STDIN_FILENO) && isatty(STDERR_FILENO);

	if (shell->interactive)
		rl_outstream = stderr;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;
	int		status;

	(void) argc;
	(void) argv;
	shell = shell_init(envp);
	if (!shell)
		return (1);
	check_interactive_mode(shell);
	shell_loop(shell);
	status = shell->last_status;
	shell_cleanup(shell);
	return (status);
}
