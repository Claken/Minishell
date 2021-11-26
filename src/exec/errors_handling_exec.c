/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:27:59 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/24 19:06:44 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void
	ft_errors_handling(t_data *d, int curr, int j, int *ret)
{
	int	cmd;
	int	exist;

	cmd = find_the_command(d, curr, j);
	exist = 0;
	if (d->token[curr].in == -1 || d->token[curr].out == -1)
	{
		ft_print_error_message(NULL, NULL, strerror(errno));
		*ret = 1;
	}
	else
	{
		if (!ft_strchr(d->token[cmd].str, '/') && path_exist(d->env))
		{
			ft_print_error_message(d->token[cmd].str, NULL,
				"Command not found");
			exist = 1;
		}
		else
			ft_print_error_message(d->token[cmd].str, NULL, strerror(errno));
		if (errno == 13 && exist == 0)
			*ret = 126;
		else
			*ret = 127;
	}
}
