/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

static int	is_quote_char(char c)
{
	return (c == '\'' || c == '"');
}

static void	handle_quote_removal(char *src, char *dst, int *i, int *j)
{
	char	quote;

	if (is_quote_char(src[*i]))
	{
		quote = src[*i];
		(*i)++;
		while (src[*i] && src[*i] != quote)
		{
			dst[*j] = src[*i];
			(*j)++;
			(*i)++;
		}
		if (src[*i] == quote)
			(*i)++;
	}
	else
	{
		dst[*j] = src[*i];
		(*j)++;
		(*i)++;
	}
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = safe_malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
		handle_quote_removal(str, result, &i, &j);
	result[j] = '\0';
	return (result);
}
