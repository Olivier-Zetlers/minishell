/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <sys/stat.h>

int	handle_path_error(t_shell *shell, char *cmd)
{
	struct stat	st;
	char		*path_env;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
				return (report_isdir(cmd));
			if (access(cmd, X_OK) != 0)
			{
				print_errno_error(cmd, NULL);
				return (126);
			}
		}
		return (report_not_found(cmd));
	}
	path_env = env_get(shell->env, "PATH");
	if (!path_env || !*path_env)
		return (report_not_found(cmd));
	return (report_cmdnf(cmd));
}
