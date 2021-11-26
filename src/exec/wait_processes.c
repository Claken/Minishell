/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 05:22:32 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/24 17:39:32 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void
	ft_for_waiting(t_exec *exec)
{
	int	prowait;
	int	wstatut;
	int	id;
	int	*global;

	global = ft_return_global();
	*global = 1000;
	prowait = 0;
	id = 0;
	while (prowait != -1)
	{
		prowait = wait(&wstatut);
		if (prowait > id)
		{
			id = prowait;
			if (WIFSIGNALED(wstatut))
				exec->ret = WTERMSIG(wstatut) + 128;
			else
				exec->ret = WEXITSTATUS(wstatut);
		}
	}
	if (exec->ret == 131)
		write(2, "Quit\n", 5);
	*global = 0;
}
