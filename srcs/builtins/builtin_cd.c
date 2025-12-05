/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include <pwd.h>
#include <unistd.h>

static char	*expand_tilde(t_shell *shell, char *path)
{
	char			*home;
	struct passwd	*pwd;

	if (!path || path[0] != '~')
		return (NULL);
	home = env_get(shell->env, "HOME");
	if (!home)
	{
		pwd = getpwuid(getuid());
		if (pwd)
			home = pwd->pw_dir;
	}
	if (!home)
		return (NULL);
	if (path[1] == '\0')
		return (ft_strdup(home));
	if (path[1] == '/')
		return (ft_strjoin(home, path + 1));
	return (NULL);
}

static char	*get_target_dir(t_shell *shell, char **argv)
{
	if (!argv[1] || !argv[1][0])
		return (env_get(shell->env, "HOME"));
	if (ft_strncmp(argv[1], "-", 2) == 0)
		return (env_get(shell->env, "OLDPWD"));
	return (argv[1]);
}

static int	update_pwd_env(t_shell *shell, char *old_pwd)
{
	char	new_pwd[4096];

	if (old_pwd && old_pwd[0])
		env_set(&shell->env, "OLDPWD", old_pwd);
	if (getcwd(new_pwd, sizeof(new_pwd)))
		env_set(&shell->env, "PWD", new_pwd);
	return (0);
}

static int	do_chdir_update(t_shell *shell, char *target, char *expanded)
{
	char	old_pwd[4096];

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd[0] = '\0';
	if (chdir(target) == -1)
	{
		free(expanded);
		print_errno_error("cd", target);
		return (1);
	}
	free(expanded);
	return (update_pwd_env(shell, old_pwd));
}

int	builtin_cd(t_shell *shell, char **argv)
{
	char	*target;
	char	*expanded;

	if (argv[1] && argv[1][0] && argv[2] && argv[2][0])
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	target = get_target_dir(shell, argv);
	expanded = expand_tilde(shell, target);
	if (expanded)
		target = expanded;
	if (!target || !*target)
	{
		free(expanded);
		print_error("cd", "HOME not set");
		return (1);
	}
	return (do_chdir_update(shell, target, expanded));
}
