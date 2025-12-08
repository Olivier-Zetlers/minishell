/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:11:32 by ozetlers          #+#    #+#             */
/*   Updated: 2024/11/29 17:11:34 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	size_t				i;
	unsigned char		target;

	p = (const unsigned char *) s;
	target = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (p[i] == target)
			return ((void *)(p + i));
		i++;
	}
	return (NULL);
}
