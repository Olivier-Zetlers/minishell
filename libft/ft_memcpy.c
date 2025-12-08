/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:12:00 by ozetlers          #+#    #+#             */
/*   Updated: 2024/11/29 17:28:00 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*src_temp;
	unsigned char	*dest_temp;

	if (!dest && !src && n != 0)
		return (NULL);
	if (n == 0)
		return (dest);
	src_temp = (unsigned char *) src;
	dest_temp = (unsigned char *) dest;
	while (n > 0)
	{
		*dest_temp++ = *src_temp++;
		n--;
	}
	return (dest);
}
