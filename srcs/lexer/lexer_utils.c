/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	is_fd_redir(char *str)
{
	int	i;

	i = 0;
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}

static t_token_type	check_double_operator(char *str, int *len)
{
	if (str[0] == '<' && str[1] == '<')
	{
		*len = 2;
		return (TOKEN_DLESS);
	}
	if (str[0] == '>' && str[1] == '>')
	{
		*len = 2;
		return (TOKEN_DGREAT);
	}
	return (TOKEN_EOF);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

t_token_type	get_operator_type(char *str, int *len)
{
	t_token_type	type;
	int				i;

	i = 0;
	if (is_fd_redir(str))
	{
		while (ft_isdigit(str[i]))
			i++;
	}
	type = check_double_operator(&str[i], len);
	if (type != TOKEN_EOF)
	{
		*len += i;
		return (type);
	}
	if (str[i] == '|')
		return (*len = i + 1, TOKEN_PIPE);
	if (str[i] == '<')
		return (*len = i + 1, TOKEN_LESS);
	if (str[i] == '>')
		return (*len = i + 1, TOKEN_GREAT);
	return (*len = 0, TOKEN_EOF);
}
