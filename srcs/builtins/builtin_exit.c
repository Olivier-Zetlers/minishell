/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include <limits.h>

static int	check_ovf(unsigned long long n, int sign, char c)
{
	unsigned long long	max_div;
	unsigned long long	max_mod;
	unsigned long long	digit;

	digit = (unsigned long long)(c - '0');
	if (sign == 1)
	{
		max_div = (unsigned long long)LLONG_MAX / 10;
		max_mod = (unsigned long long)LLONG_MAX % 10;
		if (n > max_div || (n == max_div && digit > max_mod))
			return (1);
	}
	else
	{
		max_div = ((unsigned long long)LLONG_MAX + 1) / 10;
		max_mod = ((unsigned long long)LLONG_MAX + 1) % 10;
		if (n > max_div || (n == max_div && digit > max_mod))
			return (1);
	}
	return (0);
}

static char	*skip_whitespace(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

static int	parse_arg(char *str, long long *result)
{
	int					sign;
	unsigned long long	num;

	str = skip_whitespace(str);
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	if (!*str || !isdigit(*str))
		return (0);
	num = 0;
	while (*str && isdigit(*str))
	{
		if (check_ovf(num, sign, *str))
			return (0);
		num = num * 10 + (*str - '0');
		str++;
	}
	str = skip_whitespace(str);
	if (*str)
		return (0);
	*result = sign * (long long)num;
	return (1);
}

static int	handle_error(char *arg)
{
	//	write(1, "exit\n", 5);                 <-- needs to be restored after testing
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
	exit(2);
}

int	builtin_exit(t_shell *shell, char **argv)
{
	long long	num;
	int			exit_code;

	if (!argv[1])
	{
		// write(1, "exit\n", 5);              <-- needs to be restored after testing
		exit(shell->last_status);
	}
	if (!parse_arg(argv[1], &num))
		handle_error(argv[1]);
	if (argv[2])
	{
		// write(1, "exit\n", 5);              <-- needs to be restored after testing
		print_error("exit", "too many arguments");
		return (1);
	}
	//write(1, "exit\n", 5);                       <-- needs to be restored after testing
	exit_code = (int)(num % 256);
	if (exit_code < 0)
		exit_code += 256;
	exit(exit_code);
}
