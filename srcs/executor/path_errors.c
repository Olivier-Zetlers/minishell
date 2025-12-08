/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_errors.c                                      :+:      :+:    :+:   */
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
#include <errno.h>

int	report_not_found(const char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": No such file or directory\n", 28);
	return (127);
}

int	report_isdir(const char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Is a directory\n", 17);
	return (126);
}

int	report_cmdnf(const char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	return (127);
}

int	is_directory(const char *p)
{
	struct stat	st;

	if (lstat(p, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

int	try_exec_no_search(char **argv, char **envp)
{
	if (argv[0][0] == '\0')
		return (report_not_found(""));
	if (is_directory(argv[0]))
		return (report_isdir(argv[0]));
	if (access(argv[0], X_OK) == 0)
		execve(argv[0], argv, envp);
	if (errno == EACCES)
	{
		print_errno_error(argv[0], NULL);
		return (126);
	}
	return (report_not_found(argv[0]));
}
