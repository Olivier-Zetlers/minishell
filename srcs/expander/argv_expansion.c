/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

int	count_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv && argv[count])
		count++;
	return (count);
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

char	**create_single_field(char *str)
{
	char	**single;

	single = safe_malloc(sizeof(char *) * 2);
	if (!single)
		return (NULL);
	single[0] = str;
	single[1] = NULL;
	return (single);
}

void	populate_new_argv(t_shell *shell, char **old, char **new)
{
	char	**fields;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	while (old[i])
	{
		fields = expand_and_split_token(shell, old[i]);
		if (fields)
		{
			j = 0;
			while (fields[j])
			{
				new[k] = fields[j];
				k++;
				j++;
			}
			free(fields);
		}
		i++;
	}
	new[k] = NULL;
}

int	check_ambiguous_redirect(char *original, char **fields)
{
	if (!fields || !fields[0] || fields[1])
	{
		write(2, "minishell: ", 11);
		write(2, original, ft_strlen(original));
		write(2, ": ambiguous redirect\n", 21);
		return (1);
	}
	return (0);
}
