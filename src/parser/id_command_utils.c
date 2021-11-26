/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:16:24 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/19 21:01:00 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_fct(char *cmd)
{
	int			i;
	const char	*builtin[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", "ECHO", "PWD", "ENV", NULL};

	if (!cmd)
		return (0);
	i = 0;
	while (builtin[i])
	{
		if (ft_strncmp(cmd, builtin[i], ft_strlen(cmd)) == 0
			&& ft_strncmp(cmd, builtin[i], ft_strlen(builtin[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_paths(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ":");
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin_three(paths[i], "/", cmd);
		if (access(path, F_OK) == 0)
		{
			paths = free_ind(paths);
			return (path);
		}
		free_line(&path);
		i++;
	}
	paths = free_ind(paths);
	return (NULL);
}

int	other_fct(char *cmd, char **env)
{
	char	*fct;

	fct = ft_paths(cmd, env);
	if (fct != 0)
	{
		free_line(&fct);
		return (1);
	}
	return (0);
}

void	builtin_exist(t_cmd *cmd)
{
	cmd->exist = 1;
	cmd->builtin = 1;
}
