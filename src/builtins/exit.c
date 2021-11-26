/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:11:36 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/24 19:31:19 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int
	check_if_completely_numeric(char *arg)
{
	int	i;

	i = -1;
	if (arg[0] == 43 || arg[0] == 45)
		i++;
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_print_error_message("exit", arg, "numeric argument required");
			return (0);
		}
	}
	return (1);
}

int
	ft_exit(char **args, t_data *data)
{
	int	ret;
	int	i;

	ret = 0;
	i = count_strs(args);
	if (check_type(data, PIPE) == -1)
		write(STDOUT_FILENO, "exit\n", 5);
	if (i > 1 && !check_if_completely_numeric(args[1]))
		ret = RET;
	else if (i > 2)
	{
		ft_print_error_message("exit", NULL, "too many arguments");
		return (1);
	}
	else if (i > 1)
		ret = ft_atoi(args[1]);
	else
		ret = ft_atoi(data->env[0] + 2);
	data = free_data(data);
	exit(ret);
	return (ret);
}
