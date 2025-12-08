/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quoted_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <login>                                      +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:00:00 by <login>           #+#    #+#             */
/*   Updated: 2025/12/08 00:00:00 by <login>          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

char	**split_quoted_token(char *expanded)
{
	char	**fields;
	char	*unquoted;
	int		i;

	fields = split_on_whitespace(expanded);
	if (!fields)
		return (create_single_field(ft_strdup("")));
	i = 0;
	while (fields[i])
	{
		unquoted = remove_quotes(fields[i]);
		free(fields[i]);
		if (!unquoted)
			return (NULL);
		fields[i] = unquoted;
		i++;
	}
	return (fields);
}
