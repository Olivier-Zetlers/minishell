/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static int	count_args(char **argv)
{
	int	count;

	count = 0;
	if (!argv)
		return (0);
	while (argv[count])
		count++;
	return (count);
}

static char	**copy_argv(char **old_argv, int old_count)
{
	char	**new_argv;
	int		i;

	new_argv = safe_malloc(sizeof(char *) * (old_count + 2));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < old_count)
	{
		new_argv[i] = old_argv[i];
		i++;
	}
	new_argv[old_count] = NULL;
	new_argv[old_count + 1] = NULL;
	return (new_argv);
}

int	cmd_add_arg(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_argv;
	char	*arg_copy;

	if (!cmd || !arg)
		return (0);
	count = count_args(cmd->argv);
	new_argv = copy_argv(cmd->argv, count);
	if (!new_argv)
		return (0);
	arg_copy = ft_strdup(arg);
	if (!arg_copy)
	{
		free(new_argv);
		return (0);
	}
	new_argv[count] = arg_copy;
	new_argv[count + 1] = NULL;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = new_argv;
	return (1);
}
