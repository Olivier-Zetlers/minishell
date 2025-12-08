/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/12/08 20:41:46 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "signals.h"

static int	get_shlvl_value(t_env *env)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = env_get(env, "SHLVL");
	if (!shlvl_str)
		return (0);
	shlvl = ft_atoi(shlvl_str);
	return (shlvl);
}

static void	update_shlvl(t_env *env[])
{
	int		shlvl;
	char	*new_val;

	shlvl = get_shlvl_value(*env);
	shlvl++;
	if (shlvl > 999)
		shlvl = 1;
	new_val = ft_itoa(shlvl);
	if (new_val)
	{
		env_set(env, "SHLVL", new_val);
		free(new_val);
	}
}

t_shell	*shell_init(char *envp[])
{
	/* Start of debug lines */
	int i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "SHLVL=", 6) == 0)
			fprintf(stderr, "DEBUG: Received %s\n", envp[i]);
		i++;
	}


	/* End of debug lines*/
	t_shell	*shell;

	shell = safe_malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = env_init(envp);
	update_shlvl(&shell->env);
	shell->last_status = 0;
	shell->running = 1;
	shell->interactive = 0;
	shell->in_heredoc = 0;
	return (shell);
}

void	init_shell_signals(t_shell *shell)
{
	if (shell->interactive)
	{
		rl_catch_signals = 0;
		rl_catch_sigwinch = 0;
		setup_signals(SIG_INTERACTIVE);
	}
	else
		signal(SIGINT, SIG_DFL);
}
