/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 04:25:27 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/24 20:31:31 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void
	close_in_and_out_if(t_data *data, int curr, int i, int j)
{
	int	check1;
	int	check2;

	check1 = check_type_in_command(data, RED_IN, i, j);
	check2 = check_type_in_command(data, RED_DIN, i, j);
	if (data->token[curr].in != 0 && (check1 != -1 || check2 != -1))
	{
		close(data->token[curr].in);
		if (data->token[curr].in != -1)
			data->token[curr].in = 0;
	}
	check1 = check_type_in_command(data, RED_OUT, i, j);
	check2 = check_type_in_command(data, RED_DOUT, i, j);
	if (data->token[curr].out != 1 && (check1 != -1 || check2 != -1))
	{
		close(data->token[curr].out);
		if (data->token[curr].out != -1)
			data->token[curr].out = 1;
	}
}

static void
	handle_red_d_out(t_data *data, int curr, int i)
{
	data->token[curr].out = open(data->token[i + 1].str,
			O_WRONLY | O_APPEND | CLEX);
	if (data->token[curr].out == -1)
		data->token[curr].out = open(data->token[i + 1].str,
				O_CREAT | O_WRONLY | O_TRUNC | CLEX, 00664);
}

static void
	handle_red_in(t_data *data, int curr, int i)
{
	if (data->token[curr].in != STDIN_FILENO)
		close(data->token[curr].in);
	data->token[curr].in = open(data->token[i + 1].str,
			O_RDONLY | CLEX);
}

int
	handle_redirections(t_data *data, int curr, int j, int *fd)
{
	int	i;

	i = check_type_in_command(data, REDIR, curr, j);
	while (i != -1
		&& (data->token[curr].in != -1 && data->token[curr].out != -1))
	{
		if (data->token[i].type == RED_DOUT)
			handle_red_d_out(data, curr, i);
		else if (data->token[i].type == RED_OUT)
		{
			data->token[curr].out = open(data->token[i + 1].str,
					O_CREAT | O_WRONLY | O_TRUNC | CLEX, 00664);
		}
		else if (data->token[i].type == RED_IN)
			handle_red_in(data, curr, i);
		else if (data->token[i].type == RED_DIN)
		{
			if (data->token[curr].in != STDIN_FILENO)
				close(data->token[curr].in);
			data->token[curr].in = dup(*fd);
		}
		close_in_and_out_if(data, curr, i + 1, j);
		i = check_type_in_command(data, REDIR, i + 1, j);
	}
	return (1);
}

int
	handle_double_redir_in(t_data *data, int curr, int j)
{
	int	check;
	int	heredoc;

	check = check_type_in_command(data, RED_DIN, curr, j);
	heredoc = -1;
	while (check != -1)
	{
		heredoc = ft_heredoc(data->token[check + 1].str,
				data, curr, data->token[check + 1].quotes);
		if (heredoc == 0)
			return (0);
		check = check_type_in_command(data, RED_DIN, check + 1, j);
		if (check != -1)
		{
			close(data->token[curr].in);
			data->token[curr].in = STDIN_FILENO;
		}
	}
	return (heredoc);
}
