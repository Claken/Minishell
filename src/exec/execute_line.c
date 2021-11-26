/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:11:35 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/25 02:42:49 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void
	close_in_and_out(t_data *data, int curr)
{
	if (data->token[curr].in != STDIN_FILENO
		&& data->token[curr].in != -1)
		close(data->token[curr].in);
	if (data->token[curr].out != STDOUT_FILENO
		&& data->token[curr].out != -1)
		close(data->token[curr].out);
}

static void
	end_of_exec(t_data *data, t_exec *exec, int pi[])
{
	close_pipes(exec->checkpipe, pi);
	ft_for_waiting(exec);
	update_exit_status(exec->ret, data);
}

static void
	end_of_loop(t_data *data, t_exec *exec)
{
	close_in_and_out(data, exec->i);
	exec->i = exec->j + 1;
}

void
	execute_line(t_data *d)
{
	int		pi[2];
	t_exec	exec;

	set_struct_exec(&exec);
	while (exec.i < d->token_nb)
	{
		if (!set_delimiter_and_pipe(d, &exec, pi))
			return ;
		if (!set_in_and_out(d, exec.i, exec.j, pi))
		{
			close_in_and_out(d, exec.i);
			exec.ret = 130;
			break ;
		}
		exec.cmd = find_the_command(d, exec.i, exec.j);
		if (exec.cmd != -1)
		{
			if (d->token[exec.cmd].cmd.builtin && check_type(d, PIPE) == -1)
				exec_builtin_w_out_pipe(d, &exec);
			else if (exec_fork(d, &exec, pi))
				return ;
		}
		end_of_loop(d, &exec);
	}
	end_of_exec(d, &exec, pi);
}
