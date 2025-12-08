/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_env_args(char **argv, int *has_opt, int *first_operand)
{
	int	i;

	*has_opt = 0;
	*first_operand = 0;
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1])
			*has_opt = 1;
		else if (!*first_operand)
			*first_operand = i;
		i++;
	}
	return (i > 1);
}

static void	print_operand_error(char **argv, int first_operand)
{
	int	i;

	i = first_operand;
	write(2, "minishell: env: '", 17);
	while (argv[i])
	{
		write(2, argv[i], strlen(argv[i]));
		if (argv[i + 1])
			write(2, " ", 1);
		i++;
	}
	write(2, "': No such file or directory\n", 29);
}

int	builtin_env(t_shell *shell, char **argv)
{
	t_env	*current;
	int		has_option;
	int		first_operand;

	if (!check_env_args(argv, &has_option, &first_operand))
	{
		current = shell->env;
		while (current)
		{
			if (current->value)
				printf("%s=%s\n", current->key, current->value);
			current = current->next;
		}
	}
	if (has_option)
	{
		write(2, "minishell: env: invalid option\n", 31);
		return (2);
	}
	if (first_operand)
	{
		print_operand_error(argv, first_operand);
		return (127);
	}
	return (0);
}
