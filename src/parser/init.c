/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:43:42 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/24 17:36:36 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_data(t_data *data)
{
	data->token_nb = 0;
	data->token = NULL;
	data->path = NULL;
}

void	init_token(t_token *token)
{
	token->str = NULL;
	token->redir = 0;
	token->index = 0;
	token->type = 0;
	token->cmd.cmd = NULL;
	token->cmd.builtin = 0;
	token->cmd.exist = 0;
	token->in = STDIN_FILENO;
	token->out = STDOUT_FILENO;
	token->param = NULL;
	token->quotes = 0;
}

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->builtin = 0;
	cmd->exist = 0;
}
