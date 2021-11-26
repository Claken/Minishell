/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_for_env_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:41:37 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/24 17:12:21 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char
	**cpy_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (NULL);
	}
	env[i] = 0;
	return (env);
}

char
	*find_var_in_env(char *var, char **env)
{
	int		i;
	char	*trimed;
	char	*envvar;

	i = -1;
	trimed = ft_get_var_name(var);
	if (!trimed)
		return (NULL);
	while (env[++i])
	{
		envvar = ft_get_var_name(env[i]);
		if (!envvar)
			return (NULL);
		if (!ft_strcmp(envvar, trimed))
		{
			free(envvar);
			free(trimed);
			return (env[i]);
		}
		free(envvar);
	}
	free(trimed);
	return (NULL);
}

int
	join_or_replace(char *var, char **env, int boolean)
{
	int		len;
	char	*vari;
	char	*new;
	int		i;

	vari = find_var_in_env(var, env);
	if (!boolean)
		new = ft_strjoin(vari, ft_strchr(var, '=') + 1);
	else
		new = ft_strdup(var);
	if (!new)
		return (0);
	i = 0;
	len = ft_strlen(vari);
	while (ft_strncmp(env[i], vari, len) != 0)
		i++;
	free(env[i]);
	env[i] = new;
	return (1);
}
