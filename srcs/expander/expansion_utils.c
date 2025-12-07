/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

static char	*process_expansion(t_shell *shell, char *str, int *pos, int in_dq)
{
	char	*var_name;
	char	*value;
	int		len;

	var_name = extract_var_name(&str[*pos], &len);
	if (!var_name)
	{
		if (!in_dq && (str[*pos + 1] == '"' || str[*pos + 1] == '\''))
		{
			(*pos)++;
			return (ft_strdup(""));
		}
		(*pos)++;
		return (ft_strdup("$"));
	}
	value = expand_variable(shell, var_name);
	free(var_name);
	*pos += len;
	return (value);
}

static void	append_to_result(char **result, char *str, int is_char)
{
	char	*tmp;
	char	*new;
	char	buf[2];

	if (is_char)
	{
		buf[0] = str[0];
		buf[1] = '\0';
		str = buf;
	}
	if (!str || !*str)
		return ;
	if (!*result)
	{
		*result = ft_strdup(str);
		return ;
	}
	tmp = *result;
	new = ft_strjoin(tmp, str);
	free(tmp);
	*result = new;
}

static int	get_quote_state(char *str, int pos)
{
	int	dq;
	int	sq;
	int	j;

	dq = 0;
	sq = 0;
	j = -1;
	while (++j < pos)
	{
		if (str[j] == '\'' && !sq && !dq)
			sq = 1;
		else if (str[j] == '\'' && sq)
			sq = 0;
		else if (str[j] == '"' && !sq && !dq)
			dq = 1;
		else if (str[j] == '"' && dq)
			dq = 0;
	}
	return (dq);
}

static void	process_char(t_shell *shell, char *str, int *i, char **result)
{
	char	*expanded;

	if (str[*i] == '$' && str[*i + 1])
	{
		expanded = process_expansion(shell, str, i, get_quote_state(str, *i));
		append_to_result(result, expanded, 0);
		free(expanded);
	}
	else
		append_to_result(result, &str[(*i)++], 1);
}

char	*expand_string(t_shell *shell, char *str)
{
	char	*result;
	int		i;
	int		in_single;

	result = NULL;
	i = 0;
	in_single = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !get_quote_state(str, i) && !in_single)
			in_single = 1;
		else if (str[i] == '\'' && !get_quote_state(str, i) && in_single)
			in_single = 0;
		if (str[i] != '$' || in_single || !str[i + 1])
			append_to_result(&result, &str[i++], 1);
		else
			process_char(shell, str, &i, &result);
	}
	if (!result)
		return (ft_strdup(""));
	return (result);
}
