/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

int	is_valid_var_char(char c, int first)
{
	if (first)
		return (isalpha(c) || c == '_');
	return (isalnum(c) || c == '_');
}

static char	*extract_braced_var(char *str, int *len)
{
	int		i;
	char	*name;

	i = 2;
	while (str[i] && str[i] != '}')
		i++;
	if (str[i] != '}')
	{
		*len = 0;
		return (NULL);
	}
	*len = i + 1;
	if (i == 2)
		return (ft_strdup(""));
	name = ft_substr(str, 2, i - 2);
	return (name);
}

char	*extract_var_name(char *str, int *len)
{
	int		i;
	char	*name;

	*len = 0;
	if (!str || str[0] != '$')
		return (NULL);
	if (str[1] == '?')
	{
		*len = 2;
		return (ft_strdup("?"));
	}
	if (str[1] == '{')
		return (extract_braced_var(str, len));
	if (!is_valid_var_char(str[1], 1))
		return (NULL);
	i = 1;
	while (str[i] && is_valid_var_char(str[i], 0))
		i++;
	*len = i;
	name = ft_substr(str, 1, i - 1);
	return (name);
}

char	*expand_variable(t_shell *shell, char *var_name)
{
	char	*value;

	if (!var_name)
		return (ft_strdup(""));
	if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(shell->last_status));
	value = env_get(shell->env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}
