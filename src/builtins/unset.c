/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:11:56 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/18 15:12:06 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int
	check_valid_char_for_unset(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		ft_print_error_message("unset", arg, "invalid parameter name");
		return (0);
	}
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_print_error_message("unset", arg, "invalid parameter name");
			return (0);
		}
	}
	return (1);
}

static char
	**realloc_and_remove(char **envp, char *var)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * i);
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	while (envp[++i])
	{
		if (envp[i] != var)
		{
			new[j] = ft_strdup(envp[i]);
			if (!new[j++])
				return (NULL);
		}
	}
	new[j] = 0;
	free_ind(envp);
	return (new);
}

static int
	find_var_and_realloc(char *arg, char ***new)
{
	char	*var;

	var = find_var_in_env(arg, *new);
	if (var)
	{
		*new = realloc_and_remove(*new, var);
		if (!*new)
			return (0);
	}
	return (1);
}

int
	ft_unset(char **args, char ***env, t_data *data)
{
	int		ret;
	int		i;
	char	**new;

	ret = 0;
	i = 0;
	new = cpy_env(*env);
	if (!new)
		return (1);
	while (args[++i])
	{
		if (!check_valid_char_for_unset(args[i]))
			ret = 1;
		else
		{
			if (!find_var_and_realloc(args[i], &new))
				return (1);
			else if (!ft_strcmp("PATH", args[i]))
				data->path = free_ind(data->path);
		}
	}
	free_ind(*env);
	*env = new;
	return (ret);
}
