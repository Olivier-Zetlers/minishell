/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:13:49 by ozetlers          #+#    #+#             */
/*   Updated: 2024/11/29 17:13:52 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_clean_tab(char **tab, size_t tab_index)
{
	size_t	j;

	j = 0;
	while (j < tab_index)
		free(tab[j++]);
	free(tab);
	return (-1);
}

static size_t	ft_wc(const char *s, char c)
{
	size_t	i;
	size_t	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			wc++;
		i++;
	}
	return (wc);
}

static void	fill_tab(char *new, const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
}

static int	ft_setmem(char **tab, const char *s, char c)
{
	size_t	i;
	size_t	tab_index;
	size_t	word_len;

	i = 0;
	tab_index = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		word_len = 0;
		while (s[i + word_len] && s[i + word_len] != c)
			word_len++;
		if (word_len > 0)
		{
			tab[tab_index] = malloc(sizeof(char) * (word_len + 1));
			if (!tab[tab_index])
				return (ft_clean_tab(tab, tab_index));
			fill_tab(tab[tab_index], s + i, c);
			tab_index++;
			i += word_len;
		}
	}
	tab[tab_index] = NULL;
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	size_t	wc;

	wc = ft_wc(s, c);
	tab = malloc(sizeof(char *) * (wc + 1));
	if (!tab)
		return (NULL);
	if (ft_setmem(tab, s, c) < 0)
		return (NULL);
	return (tab);
}
