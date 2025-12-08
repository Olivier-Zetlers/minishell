/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"

int	execute_redirections_only(t_cmd *cmd)
{
	int	saved_fds[3];

	save_standard_fds(saved_fds);
	if (setup_redirections(cmd->redirects) == -1)
	{
		restore_standard_fds(saved_fds);
		return (1);
	}
	restore_standard_fds(saved_fds);
	return (0);
}

int	execute_single_builtin(t_shell *shell, t_cmd *cmd)
{
	int	saved_fds[3];
	int	status;

	save_standard_fds(saved_fds);
	if (setup_redirections(cmd->redirects) == -1)
	{
		restore_standard_fds(saved_fds);
		return (1);
	}
	status = execute_builtin(shell, cmd->argv);
	restore_standard_fds(saved_fds);
	return (status);
}
