/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static const t_builtin	*get_builtins(void)
{
	static const t_builtin	builtins[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{NULL, NULL}
	};

	return (builtins);
}

int	is_builtin(char *cmd)
{
	const t_builtin	*builtins;
	int				i;

	if (!cmd)
		return (0);
	builtins = get_builtins();
	i = 0;
	while (builtins[i].name)
	{
		if (ft_strncmp(cmd, builtins[i].name,
				ft_strlen(builtins[i].name) + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute_builtin(t_shell *shell, char **argv)
{
	const t_builtin	*builtins;
	int				i;

	if (!argv || !argv[0])
		return (1);
	builtins = get_builtins();
	i = 0;
	while (builtins[i].name)
	{
		if (ft_strncmp(argv[0], builtins[i].name,
				ft_strlen(builtins[i].name) + 1) == 0)
			return (builtins[i].func(shell, argv));
		i++;
	}
	return (1);
}
