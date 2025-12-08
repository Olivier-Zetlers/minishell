/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:11:15 by ozetlers          #+#    #+#             */
/*   Updated: 2024/11/29 17:11:19 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_num_len(int n)
{
	size_t		len;
	long long	temp;

	temp = (long long) n;
	if (temp == 0)
		return (1);
	len = 0;
	if (temp < 0)
	{
		temp *= -1;
		len++;
	}
	while (temp > 0)
	{
		temp /= 10;
		len++;
	}
	return (len);
}

unsigned int	ft_negative(long long n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	size_t		len;
	long long	temp;
	char		*str;

	len = ft_num_len(n);
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	temp = (long long) n;
	if (ft_negative(n))
	{
		str[0] = '-';
		temp *= -1;
	}
	str[len] = '\0';
	while (len > ft_negative(n))
	{
		str[--len] = temp % 10 + '0';
		temp /= 10;
	}
	return (str);
}
