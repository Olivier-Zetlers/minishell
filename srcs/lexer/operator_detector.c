/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_detector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_double_operator(char first, char second)
{
	if (first == '<' && second == '<')
		return (1);
	if (first == '>' && second == '>')
		return (1);
	return (0);
}

int	detect_operator_length(char *str)
{
	if (!str || !*str)
		return (0);
	if (is_double_operator(str[0], str[1]))
		return (2);
	if (is_operator_char(str[0]))
		return (1);
	return (0);
}
