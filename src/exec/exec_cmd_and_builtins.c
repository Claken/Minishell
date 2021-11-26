/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_and_builtins.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 04:35:21 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/25 02:41:35 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void
	exec_builtin_w_out_pipe(t_data *data, t_exec *exec)
{
	int	fd1;
	int	fd2;

	fd1 = dup(STDIN_FILENO);
	fd2 = dup(STDOUT_FILENO);
	dup2(data->token[exec->i].in, STDIN_FILENO);
	dup2(data->token[exec->i].out, STDOUT_FILENO);
	if (data->token[exec->i].in != -1 && data->token[exec->i].out != -1)
		exec->ret = exec_builtin(data->token[exec->cmd].str,
				&data->env, data->token[exec->cmd].param, data);
	else
	{
		ft_print_error_message(NULL, NULL, "Bad file descriptor");
		exec->ret = 1;
	}
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(fd1);
	close(fd2);
}

static void
	exec_builtin_w_pipe(t_data *data, t_exec *exec)
{
	if (data->token[exec->i].in != -1
		&& data->token[exec->i].out != -1)
		exec->ret = exec_builtin(data->token[exec->cmd].str,
				&data->env, data->token[exec->cmd].param, data);
	else
		ft_errors_handling(data, exec->i, exec->j, &exec->ret);
}

static void
	exec_cmd(t_data *data, t_exec *exec)
{
	char	*str;

	str = NULL;
	if (data->token[exec->cmd].cmd.exist)
		str = data->token[exec->cmd].cmd.cmd;
	else
		str = data->token[exec->cmd].str;
	if (data->token[exec->i].in != -1
		&& data->token[exec->i].out != -1)
		execve(str, data->token[exec->cmd].param, data->env);
	ft_errors_handling(data, exec->i, exec->j, &exec->ret);
}

int
	exec_fork(t_data *data, t_exec *exec, int pi[])
{
	exec->proid = fork();
	if (exec->proid < 0)
		return (1);
	if (exec->proid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (exec->checkpipe == 0)
			close(pi[0]);
		if (!data->token[exec->cmd].cmd.exist)
			close_in_and_out(data, exec->i);
		dup2(data->token[exec->i].in, STDIN_FILENO);
		dup2(data->token[exec->i].out, STDOUT_FILENO);
		if (data->token[exec->cmd].cmd.builtin)
			exec_builtin_w_pipe(data, exec);
		else
			exec_cmd(data, exec);
		data = free_data(data);
		close_pipes(exec->checkpipe, pi);
		exit(exec->ret);
	}
	return (0);
}
