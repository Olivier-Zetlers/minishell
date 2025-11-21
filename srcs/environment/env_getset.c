/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*env_get(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static void	update_env_value(t_env *node, char *value)
{
	if (node->value)
		free(node->value);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
}

static t_env	*create_env_node(char *key, char *value)
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
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	env_set(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*new_node;

	if (!env || !key)
		return ;
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			update_env_value(current, value);
			return ;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	new_node = create_env_node(key, value);
	if (!new_node)
		return ;
	if (!*env)
		*env = new_node;
	else
		current->next = new_node;
}

void	env_unset(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !*env || !key)
		return ;
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
