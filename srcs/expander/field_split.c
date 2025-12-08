/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

int	needs_expansion(char *str)
{
	int	i;
	int	in_single;

	if (!str)
		return (0);
	i = 0;
	in_single = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_single)
			in_single = 1;
		else if (str[i] == '\'' && in_single)
			in_single = 0;
		else if (str[i] == '$' && !in_single)
			return (1);
		i++;
	}
	return (0);
}

static int	count_fields(char *s)
{
	int	count;
	int	in_field;
	int	in_single;
	int	in_double;

	count = 0;
	in_field = 0;
	in_single = 0;
	in_double = 0;
	while (*s)
	{
		if (*s == '\'' && !in_double)
			in_single = !in_single;
		else if (*s == '"' && !in_single)
			in_double = !in_double;
		if (!in_single && !in_double && ft_isspace(*s))
			in_field = 0;
		else if (!in_field)
		{
			in_field = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*extract_field(char **s)
{
	char	*start;
	int		len;
	int		in_single;
	int		in_double;

	in_single = 0;
	in_double = 0;
	while (**s && ft_isspace(**s))
		(*s)++;
	start = *s;
	len = 0;
	while (**s)
	{
		if (!in_single && !in_double && ft_isspace(**s))
			break ;
		if (**s == '\'' && !in_double)
			in_single = !in_single;
		else if (**s == '"' && !in_single)
			in_double = !in_double;
		(*s)++;
		len++;
	}
	return (ft_substr(start, 0, len));
}

char	**split_on_whitespace(char *str)
{
	char	**result;
	int		count;
	int		i;

	if (!str)
		return (NULL);
	count = count_fields(str);
	result = safe_malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
	{
		result[i] = extract_field(&str);
		if (!result[i])
		{
			while (--i >= 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	has_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}
