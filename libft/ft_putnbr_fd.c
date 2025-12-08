/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:13:21 by ozetlers          #+#    #+#             */
/*   Updated: 2024/11/29 17:13:23 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char		c;
	long long	temp;

	temp = n;
	if (temp < 0)
	{
		write(fd, "-", 1);
		temp *= -1;
	}
	if (temp / 10 > 0)
		ft_putnbr_fd(temp / 10, fd);
	c = (temp % 10) + '0';
	write(fd, &c, 1);
}
