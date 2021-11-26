/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 04:32:09 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/25 02:41:40 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void
	close_pipes(int checkpipe, int pi[])
{
	if (checkpipe == 0)
	{
		close(pi[0]);
		close(pi[1]);
	}
}

int
	ft_check_if_pipe(t_data *data, int i, int j, int pi[])
{
	int	checkpipe;

	checkpipe = 1;
	if (check_type_in_command(data, PIPE, i, j) != -1)
	{
		checkpipe = pipe(pi);
		if (checkpipe < 0)
			return (-1);
	}
	return (checkpipe);
}
