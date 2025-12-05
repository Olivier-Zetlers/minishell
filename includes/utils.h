/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/* String utilities */
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_free_array(char **array);
int		ft_isspace(char c);
int		ft_isdigit(char c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

/* Memory utilities */
void	*safe_malloc(size_t size);
void	*mini_realloc(void *ptr, size_t old_size, size_t new_size);

/* Error handling */
void	print_error(char *context, char *msg);
void	print_errno_error(char *context, char *target);
void	syntax_error(char *token);
void	print_cmd_error(char *cmd);

/* Environment utilities */
t_env	*env_init(char **envp);
void	env_free(t_env *env);
char	*env_get(t_env *env, char *key);
void	env_set(t_env **env, char *key, char *value);
void	env_unset(t_env **env, char *key);
char	**env_to_array(t_env *env);

#endif
