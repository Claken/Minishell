/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 05:04:03 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/25 02:42:40 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void
	set_struct_exec(t_exec *exec)
{
	exec->i = 0;
	exec->j = 0;
	exec->cmd = 0;
	exec->checkpipe = 1;
	exec->ret = 0;
	exec->proid = 0;
}

int
	set_delimiter_and_pipe(t_data *data, t_exec *exec, int pi[])
{
	exec->j = exec->i;
	while (exec->j < data->token_nb - 1 && data->token[exec->j].type != PIPE)
		exec->j++;
	exec->checkpipe = ft_check_if_pipe(data, exec->i, exec->j, pi);
	if (exec->checkpipe == -1)
		return (0);
	return (1);
}

int
	set_in_and_out(t_data *data, int curr, int j, int pi[])
{
	int	hd;
	int	fd_hd;

	fd_hd = -2;
	if (check_type_in_command(data, REDIR, curr, j) != -1)
	{
		hd = handle_double_redir_in(data, curr, j);
		if (!hd)
			return (0);
		if (hd != -1)
			fd_hd = dup(data->token[curr].in);
		handle_redirections(data, curr, j, &fd_hd);
	}
	if (fd_hd != -2)
		close(fd_hd);
	if (check_type_in_command(data, PIPE, curr, j) != -1)
	{
		if (data->token[curr].out == STDOUT_FILENO)
			data->token[curr].out = pi[1];
		else
			close(pi[1]);
		data->token[j + 1].in = pi[0];
	}
	return (1);
}
