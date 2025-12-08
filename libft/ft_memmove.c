/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:12:15 by ozetlers          #+#    #+#             */
/*   Updated: 2024/11/29 17:12:19 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h> // for size_t

static void	backw_copy(unsigned char *dest, const unsigned char *src, size_t n);
static void	forw_copy(unsigned char *dest, const unsigned char *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *) dest;
	s = (const unsigned char *) src;
	if (d == s || n == 0)
		return (dest);
	if (d > s && d < s + n)
		backw_copy(d, s, n);
	else
		forw_copy(d, s, n);
	return (dest);
}

static void	forw_copy(unsigned char *d, const unsigned char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

// Loop structured to avoid wrap around of i to SIZE_MAX
static void	backw_copy(unsigned char *d, const unsigned char *s, size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		d[i - 1] = s[i - 1];
		i--;
	}
}
