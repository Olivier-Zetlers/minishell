/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

char	**expand_and_split_token(t_shell *shell, char *token)
{
	char	*expanded;
	char	*unquoted;
	char	**fields;

	expanded = expand_string(shell, token);
	if (!expanded)
		return (NULL);
	if (has_quotes(token))
	{
		unquoted = remove_quotes(expanded);
		free(expanded);
		return (create_single_field(unquoted));
	}
	unquoted = remove_quotes(expanded);
	free(expanded);
	if (!unquoted || !*unquoted)
	{
		free(unquoted);
		return (NULL);
	}
	fields = split_on_whitespace(unquoted);
	free(unquoted);
	return (fields);
}

static char	**rebuild_argv(t_shell *shell, char **old_argv)
{
	char	**new_argv;
	char	**fields;
	int		total;
	int		i;

	total = 0;
	i = 0;
	while (old_argv[i])
	{
		fields = expand_and_split_token(shell, old_argv[i]);
		if (fields)
			total += count_argv(fields);
		free_argv(fields);
		i++;
	}
	new_argv = safe_malloc(sizeof(char *) * (total + 1));
	if (!new_argv)
		return (NULL);
	populate_new_argv(shell, old_argv, new_argv);
	return (new_argv);
}

static void	expand_argv(t_shell *shell, t_cmd *cmd)
{
	char	**new_argv;
	char	**old_argv;

	if (!cmd->argv)
		return ;
	new_argv = rebuild_argv(shell, cmd->argv);
	if (new_argv)
	{
		old_argv = cmd->argv;
		cmd->argv = new_argv;
		free_argv(old_argv);
	}
}

static void	expand_redirects(t_shell *shell, t_redir *redirects)
{
	t_redir	*current;
	char	**fields;

	current = redirects;
	while (current)
	{
		if (current->type != REDIR_HEREDOC)
		{
			fields = expand_and_split_token(shell, current->file);
			if (check_ambiguous_redirect(current->file, fields))
			{
				free_argv(fields);
				shell->last_status = 1;
				return ;
			}
			if (fields && fields[0])
			{
				free(current->file);
				current->file = fields[0];
				free(fields);
			}
		}
		current = current->next;
	}
}

void	expand_commands(t_shell *shell, t_cmd *commands)
{
	t_cmd	*current;

	current = commands;
	while (current)
	{
		expand_argv(shell, current);
		expand_redirects(shell, current->redirects);
		current = current->next;
	}
}
