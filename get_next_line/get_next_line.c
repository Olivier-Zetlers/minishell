/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:30:37 by ozetlers          #+#    #+#             */
/*   Updated: 2025/04/10 17:30:42 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remainder;

	if (BUFFER_SIZE <= 0 || (size_t) BUFFER_SIZE > SSIZE_MAX)
		return (NULL);
	if (remainder == NULL)
	{
		remainder = (char *) malloc(sizeof(char));
		if (remainder == NULL)
			return (NULL);
		remainder[0] = '\0';
	}
	if (read_file(fd, &remainder) == 1)
		return (extract(&remainder));
	free(remainder);
	remainder = NULL;
	return (NULL);
}
