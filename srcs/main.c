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

static int	handle_c_flag(t_shell *shell, char *cmd)
{
	int	status;

	shell_execute_line(shell, cmd);
	status = shell->last_status;
	shell_cleanup(shell);
	return (status);
}

static void	check_interactive_mode(t_shell *shell)
{
	int	is_tty;

	is_tty = isatty(STDIN_FILENO) & isatty(STDERR_FILENO);
	if (is_tty)
		shell->interactive = 1;
	else
		shell->interactive = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;
	int		status;

	shell = shell_init(envp);
	if (!shell)
		return (1);
	check_interactive_mode(shell);
	if (argc >= 3 && ft_strncmp(argv[1], "-c", 3) == 0)
		return (handle_c_flag(shell, argv[2]));
	shell_loop(shell);
	status = shell->last_status;
	shell_cleanup(shell);
	return (status);
}
