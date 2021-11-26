/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_for_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:33:02 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/25 00:49:47 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int
	exec_builtin(char *built, char ***env, char **args, t_data *data)
{
	int	ret;

	ret = 1;
	if (ft_strcmp(built, "echo") == 0 || ft_strcmp(built, "ECHO") == 0)
		ret = ft_echo(args);
	else if (ft_strcmp(built, "cd") == 0)
		ret = ft_cd(args, *env);
	else if (ft_strcmp(built, "pwd") == 0 || ft_strcmp(built, "PWD") == 0)
		ret = ft_pwd();
	else if (ft_strcmp(built, "export") == 0)
		ret = ft_export(env, args);
	else if (ft_strcmp(built, "unset") == 0)
		ret = ft_unset(args, env, data);
	else if (ft_strcmp(built, "env") == 0 || ft_strcmp(built, "ENV") == 0)
		ret = ft_env(*env);
	else if (ft_strcmp(built, "exit") == 0)
		ret = ft_exit(args, data);
	return (ret);
}
