/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static void	print_env_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_var(t_shell *shell, char *arg)
{
	char	*eq_pos;
	char	*key;
	char	*value;

	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
	{
		env_set(&shell->env, arg, NULL);
		return ;
	}
	key = ft_substr(arg, 0, eq_pos - arg);
	if (!key)
		return ;
	value = ft_strdup(eq_pos + 1);
	if (!value)
	{
		free(key);
		return ;
	}
	env_set(&shell->env, key, value);
	free(key);
	free(value);
}

int	builtin_export(t_shell *shell, char **argv)
{
	int	i;
	int	status;

	if (!argv[1])
	{
		print_env_export(shell->env);
		return (0);
	}
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			print_error("export", "not a valid identifier");
			status = 1;
		}
		else
			export_var(shell, argv[i]);
		i++;
	}
	return (status);
}
