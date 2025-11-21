/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <errno.h>
#include <sys/stat.h>

void	print_error(char *context, char *msg)
{
	write(2, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
	if (context)
	{
		write(2, context, ft_strlen(context));
		write(2, ": ", 2);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	print_errno_error(char *context, char *target)
{
	write(2, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
	if (context)
	{
		write(2, context, ft_strlen(context));
		write(2, ": ", 2);
	}
	if (target)
	{
		write(2, target, ft_strlen(target));
		write(2, ": ", 2);
	}
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	syntax_error(char *token)
{
	write(2, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
	write(2, "syntax error near unexpected token `", 37);
	if (token)
		write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
}

void	print_cmd_error(char *cmd)
{
	struct stat	st;

	if (!cmd || !*cmd)
	{
		print_error(cmd, "command not found");
		return ;
	}
	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
			print_error(cmd, "Is a directory");
		else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
			print_error(cmd, "Permission denied");
		else
			print_error(cmd, "No such file or directory");
	}
	else
		print_error(cmd, "command not found");
}
