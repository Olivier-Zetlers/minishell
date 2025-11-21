/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

int	builtin_pwd(t_shell *shell, char **argv)
{
	char	cwd[4096];
	char	*pwd_env;

	(void)argv;
	if (getcwd(cwd, sizeof(cwd)))
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		return (0);
	}
	pwd_env = env_get(shell->env, "PWD");
	if (pwd_env)
	{
		write(1, pwd_env, ft_strlen(pwd_env));
		write(1, "\n", 1);
		return (0);
	}
	print_errno_error("pwd", NULL);
	return (1);
}
