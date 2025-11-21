/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolver.c                                    :+:      :+:    :+:   */
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

static int	path_search_enabled(const char *path)
{
	return (path && *path);
}

static char	*check_absolute_path(char *cmd)
{
	struct stat	st;

	if (access(cmd, F_OK) == 0)
	{
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
			return (NULL);
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	return (NULL);
}

static char	*search_in_path(char *cmd, char *path_dir)
{
	char		*full_path;
	char		*tmp;
	struct stat	st;

	tmp = ft_strjoin(path_dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) == 0)
	{
		if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode))
		{
			free(full_path);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
			return (full_path);
	}
	free(full_path);
	return (NULL);
}

static char	*search_path_env(char *cmd, char *path_env)
{
	char	**paths;
	char	*result;
	int		i;

	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	result = NULL;
	while (paths[i] && !result)
	{
		result = search_in_path(cmd, paths[i]);
		i++;
	}
	ft_free_array(paths);
	return (result);
}

char	*resolve_path(char *cmd, t_env *env)
{
	char	*path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (check_absolute_path(cmd));
	path = env_get(env, "PATH");
	if (!path_search_enabled(path))
		return (NULL);
	return (search_path_env(cmd, path));
}
