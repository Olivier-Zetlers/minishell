/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

char	*read_line_noninteractive(void)
{
	char	buf[5120];
	int		i;
	int		ret;

	i = 0;
	while (i < 5119)
	{
		ret = read(STDIN_FILENO, &buf[i], 1);
		if (ret <= 0)
		{
			if ((i == 0) && (ret == 0))
				return (NULL);
			break ;
		}
		if (buf[i] == '\n')
			break ;
		i++;
	}
	buf[i] = '\0';
	return (ft_strdup(buf));
}
