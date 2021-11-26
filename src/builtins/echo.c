/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:11:08 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/25 00:50:40 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void
	ft_write_and_change_ret(char *str, int *ret)
{
	int	ret1;

	ret1 = write(STDOUT_FILENO, str, ft_strlen(str));
	if (ret1 == -1)
	{
		ft_print_error_message("echo", NULL, strerror(errno));
		*ret = ret1;
	}
}

int
	ft_echo(char **args)
{
	int	i;
	int	opt;
	int	ret;

	i = 0;
	opt = 0;
	ret = 0;
	if (args[1] && !ft_strncmp(args[1], "-n", 3))
	{
		opt++;
		i++;
	}
	while (args[++i])
	{
		ft_write_and_change_ret(args[i], &ret);
		if (args[i + 1])
			ft_write_and_change_ret(" ", &ret);
	}
	if (!opt)
		ft_write_and_change_ret("\n", &ret);
	return (ret);
}
