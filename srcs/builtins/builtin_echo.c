/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static int	parse_flags(char *arg, int *newline, int *interpret)
{
	int	i;
	int	tmp_newline;
	int	tmp_interpret;

	if (!arg || arg[0] != '-' || !arg[1])
		return (0);
	i = 1;
	tmp_newline = *newline;
	tmp_interpret = *interpret;
	while (arg[i])
	{
		if (arg[i] == 'n')
			tmp_newline = 0;
		else if (arg[i] == 'e')
			tmp_interpret = 1;
		else
			return (0);
		i++;
	}
	*newline = tmp_newline;
	*interpret = tmp_interpret;
	return (1);
}

static void	print_escape_char(char c)
{
	if (c == 'n')
		write(1, "\n", 1);
	else if (c == 't')
		write(1, "\t", 1);
	else if (c == 'r')
		write(1, "\r", 1);
	else if (c == 'a')
		write(1, "\a", 1);
	else if (c == 'b')
		write(1, "\b", 1);
	else if (c == 'f')
		write(1, "\f", 1);
	else if (c == 'v')
		write(1, "\v", 1);
	else if (c == '\\')
		write(1, "\\", 1);
	else
	{
		write(1, "\\", 1);
		write(1, &c, 1);
	}
}

static void	print_with_escapes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			print_escape_char(str[i + 1]);
			i += 2;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}

static void	print_args(char **argv, int i, int interpret)
{
	while (argv[i])
	{
		if (interpret)
			print_with_escapes(argv[i]);
		else
			write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
}

int	builtin_echo(t_shell *shell, char **argv)
{
	int	i;
	int	newline;
	int	interpret;

	(void)shell;
	i = 1;
	newline = 1;
	interpret = 0;
	while (argv[i] && parse_flags(argv[i], &newline, &interpret))
		i++;
	print_args(argv, i, interpret);
	if (newline)
		write(1, "\n", 1);
	return (0);
}
