/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_env	*env_node_create(char *key, char *value)
{
	t_env	*node;

	node = safe_malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			free(node->key);
			free(node);
			return (NULL);
		}
	}
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

static void	env_add_back(t_env **list, t_env *new)
{
	t_env	*last;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
}

static void	parse_env_string(char *env_str, char **key, char **value)
{
	char	*eq_pos;

	eq_pos = ft_strchr(env_str, '=');
	if (eq_pos)
	{
		*key = ft_substr(env_str, 0, eq_pos - env_str);
		*value = ft_strdup(eq_pos + 1);
	}
	else
	{
		*key = ft_strdup(env_str);
		*value = NULL;
	}
}

t_env	*env_init(char *envp[])
{
	t_env	*env;
	t_env	*node;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	if (!envp || !envp[0])
		return (NULL);
	i = 0;
	while (envp[i])
	{
		parse_env_string(envp[i], &key, &value);
		if (key)
		{
			node = env_node_create(key, value);
			if (node)
				env_add_back(&env, node);
		}
		free(key);
		free(value);
		i++;
	}
	return (env);
}

void	env_free(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}
