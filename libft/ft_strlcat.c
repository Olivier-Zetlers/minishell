/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:15:05 by ozetlers          #+#    #+#             */
/*   Updated: 2024/11/29 17:15:08 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static size_t	ft_strlen(const char *s);

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	copy_len;
	size_t	dst_len;
	size_t	total_len;

	dst_len = 0;
	while (dst[dst_len] != '\0' && dst_len < size)
		dst_len++;
	total_len = dst_len + ft_strlen(src);
	if (dst_len >= size)
		return (size + ft_strlen(src));
	copy_len = size - dst_len - 1;
	if (copy_len > 0)
	{
		i = 0;
		while (i < copy_len && src[i] != '\0')
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
	}
	return (total_len);
}

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
