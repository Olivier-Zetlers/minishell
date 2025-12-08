/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:16:39 by ozetlers          #+#    #+#             */
/*   Updated: 2024/11/29 17:16:41 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;
	char		ch;

	last = NULL;
	ch = (char) c;
	while (*s != '\0')
	{
		if (*s == ch)
			last = s;
		s++;
	}
	if (ch == '\0')
		return ((char *) s);
	return ((char *) last);
}
