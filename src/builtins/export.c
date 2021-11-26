/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:11:43 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/24 17:12:05 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int
	check_valid_char_for_export(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		ft_print_error_message("export", arg, "not an identifier");
		return (0);
	}
	while (arg[++i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_'
			&& !(arg[i] == '+' && arg[i + 1] == '='))
		{
			ft_print_error_message("export",
				arg, "not valid in this context");
			return (0);
		}
	}
	return (1);
}

static char
	**realloc_and_add(char **envp, char *arg, int add)
{
	char	**new;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + add + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
			return (NULL);
	}
	new[i] = ft_strdup_w_out(arg, "+");
	if (!new[i])
		return (NULL);
	new[++i] = 0;
	free_ind(envp);
	return (new);
}

static int
	check_arg_and_choose_the_right_action(char *arg, char ***new, int *add)
{
	if (!find_var_in_env(arg, *new))
	{
		*add = *add + 1;
		*new = realloc_and_add(*new, arg, *add);
		if (!*new)
			return (0);
	}
	else
	{
		if (ft_strchr(arg, '=') && ft_strchr(arg, '+'))
		{
			if (!join_or_replace(arg, *new, 0))
				return (0);
		}
		else if (ft_strchr(arg, '='))
		{
			if (!join_or_replace(arg, *new, 1))
				return (0);
		}
	}
	return (1);
}

static void
	if_export_w_out_arg(char **args, char **env)
{
	if (count_strs(args) == 1)
		print_export(env + 1);
}

int
	ft_export(char ***env, char **args)
{
	int		ret;
	char	**new;
	int		add;
	int		i;

	ret = 0;
	add = 0;
	new = cpy_env(*env);
	i = 0;
	if (!new)
		return (1);
	while (args[++i])
	{
		if (!check_valid_char_for_export(args[i]))
			ret = 1;
		else if (!check_arg_and_choose_the_right_action(args[i], &new, &add))
			return (1);
	}
	if_export_w_out_arg(args, *env);
	free_ind(*env);
	*env = new;
	return (ret);
}
