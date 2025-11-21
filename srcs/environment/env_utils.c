/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->value)
			count++;
		env = env->next;
	}
	return (count);
}

static char	*create_env_string(char *key, char *value)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, value);
	free(tmp);
	return (str);
}

char	**env_to_array(t_env *env)
{
	char	**array;
	int		count;
	int		i;

	count = env_count(env);
	array = safe_malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env && i < count)
	{
		if (env->value)
		{
			array[i] = create_env_string(env->key, env->value);
			if (!array[i])
			{
				ft_free_array(array);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}
