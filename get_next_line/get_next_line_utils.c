/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:30:54 by ozetlers          #+#    #+#             */
/*   Updated: 2025/04/10 17:30:57 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	findlen(const char *s, int c);
static char		*custom_strjoin(char *s1, const char *s2);
static char		*ft_substr(char const *s, unsigned int start, size_t len);

static char	*custom_strjoin(char *s1, const char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = (char *) malloc(findlen(s1, '\0') + findlen(s2, '\0') + 1);
	if (res == NULL || s1 == NULL || s2 == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}

// If c != '\0', returns 0-based index of c, else returns string length 
static ssize_t	findlen(const char *s, int c)
{
	size_t	pos;

	if (s == NULL)
		return (-1);
	pos = 0;
	while (s[pos])
	{
		if (s[pos] == (char) c)
			return (pos);
		pos++;
	}
	if (c == '\0')
		return (pos);
	return (-1);
}

char	*extract(char **rem)
{
	char	*tmp[2];

	if (findlen(*rem, '\n') >= 0)
	{
		tmp[0] = ft_substr(*rem, 0, findlen(*rem, '\n') + 1);
		tmp[1] = ft_substr(*rem, findlen(*rem, '\n') + 1, findlen(*rem, '\0'));
		if (tmp[0] == NULL || tmp[1] == NULL)
		{
			free(tmp[0]);
			return (NULL);
		}
		free(*rem);
		*rem = tmp[1];
		return (tmp[0]);
	}
	else if (findlen(*rem, '\0') >= 1)
	{
		tmp[0] = ft_substr(*rem, 0, findlen(*rem, '\n'));
		free(*rem);
		*rem = NULL;
		return (tmp[0]);
	}
	free(*rem);
	*rem = NULL;
	return (NULL);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*str;

	s_len = findlen(s, '\0');
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	read_file(int fd, char **remainder)
{
	char	*buf;
	ssize_t	read_bytes;

	buf = (char *) malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (1);
	read_bytes = BUFFER_SIZE;
	while ((read_bytes == BUFFER_SIZE) && (findlen(*remainder, '\n') == -1))
	{
		read_bytes = read(fd, (void *) buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (-1);
		}
		buf[read_bytes] = '\0';
		*remainder = custom_strjoin(*remainder, buf);
		if (*remainder == NULL)
		{
			free(buf);
			return (-1);
		}
	}
	free(buf);
	return (1);
}
