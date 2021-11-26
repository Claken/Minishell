/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_for_env_02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:49:27 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/15 19:37:36 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char
	*ft_get_var_in_env(char *var, char **envp)
{
	int		i;
	char	*line;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (ft_strncmp(envp[i], var, len) != 0)
		i++;
	line = ft_strdup(envp[i]);
	if (!line)
		return (NULL);
	return (line);
}

char
	*ft_get_var_name(char *var)
{
	int		lenvar;
	char	*trimed;
	int		i;
	int		j;

	lenvar = ft_strlen(var);
	trimed = malloc(sizeof(char) * (lenvar + 1));
	if (!trimed)
		return (NULL);
	i = 0;
	j = 0;
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '+')
			trimed[j++] = var[i];
		i++;
	}
	trimed[j] = 0;
	return (trimed);
}

char
	*ft_get_var_val_in_env(char *var, char **envp)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i] && ft_strncmp(envp[i], var, len) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_strchr(envp[i], '=') + 1);
}

int
	path_exist(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	if (envp[i] == NULL)
		return (0);
	return (1);
}
