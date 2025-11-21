/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/* Built-in function type */
typedef int	(*t_builtin_func)(t_shell *shell, char **argv);

/* Built-in structure */
typedef struct s_builtin
{
	char			*name;
	t_builtin_func	func;
}	t_builtin;

/* Built-in function prototypes */
int		is_builtin(char *cmd);
int		execute_builtin(t_shell *shell, char **argv);
int		builtin_echo(t_shell *shell, char **argv);
int		builtin_cd(t_shell *shell, char **argv);
int		builtin_pwd(t_shell *shell, char **argv);
int		builtin_export(t_shell *shell, char **argv);
int		builtin_unset(t_shell *shell, char **argv);
int		builtin_env(t_shell *shell, char **argv);
int		builtin_exit(t_shell *shell, char **argv);

#endif
