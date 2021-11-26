/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:10:59 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/24 18:36:01 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int
	ft_go_to_path(char *var, char **envp, int *ret)
{
	char	*path;
	char	*phrase;

	path = ft_get_var_val_in_env(var, envp);
	if (!path)
	{
		phrase = ft_strjoin(var, " not set");
		if (!phrase)
			return (0);
		ft_print_error_message("cd", NULL, phrase);
		free(phrase);
		return (0);
	}
	else if (ft_strlen(path) > 0)
	{
		*ret = chdir(path);
		if (*ret == -1)
		{
			ft_print_error_message("cd", path, strerror(errno));
			return (0);
		}
	}
	else
		*ret = 0;
	return (1);
}

static char
	*ft_find_rep(char *rep, char **cdpath)
{
	int		i;
	char	*reppath;
	int		fd;

	i = -1;
	while (cdpath[++i])
	{
		reppath = ft_strjoin_three(cdpath[i], "/", rep);
		if (!reppath)
			return (NULL);
		fd = access(reppath, F_OK);
		if (fd == 0)
			return (reppath);
		free(reppath);
	}
	return (ft_strdup(rep));
}

static int
	serch_in_cd_path(char **envp, int *ret, char *arg)
{
	char	**cdpath;
	char	*path;

	path = ft_get_var_val_in_env("CDPATH", envp);
	cdpath = ft_split(path, ":");
	if (!cdpath)
		return (0);
	path = NULL;
	path = ft_find_rep(arg, cdpath);
	if (!path)
		return (0);
	if (ft_strcmp(path, arg))
		printf("%s\n", path);
	*ret = chdir(path);
	free(path);
	free_ind(cdpath);
	return (1);
}

static int
	too_much_args_or_no_arg(int *ret, char **envp, char **args)
{
	int	i;

	i = count_strs(args);
	if (i > 2)
	{
		ft_print_error_message("cd", NULL, "too many arguments");
		return (1);
	}
	if (i < 2)
	{
		if (!ft_go_to_path("HOME", envp, ret))
			return (1);
	}
	return (0);
}

int
	ft_cd(char **args, char **envp)
{
	int	ret;

	ret = 2;
	if (too_much_args_or_no_arg(&ret, envp, args))
		return (1);
	if (ret == 0)
		return (ret);
	else
	{
		if (ft_get_var_val_in_env("CDPATH", envp)
			&& ft_strcmp("..", args[1])
			&& ft_strcmp(".", args[1]))
		{
			if (!serch_in_cd_path(envp, &ret, args[1]))
				return (1);
		}
		else if (args[1])
			ret = chdir(args[1]);
	}
	if (ret == -1)
	{
		ft_print_error_message("cd", args[1], strerror(errno));
		return (1);
	}
	return (ret);
}
