/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:31:21 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/24 22:47:40 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int
	check_after_red(t_data *data, int i)
{
	if (i + 1 < data->token_nb)
	{
		if (data->token[i + 1].type != WORD)
			return (0);
	}
	return (1);
}

static int
	check_after_pipe(t_data *data, int i)
{
	if (i + 1 < data->token_nb)
	{
		if (data->token[i + 1].type != WORD
			&& data->token[i + 1].type < 60)
			return (0);
	}
	return (1);
}

int
	check_valid_command(t_data *data)
{
	int	i;

	i = 0;
	if (data->token[i].type == WORD && data->token_nb == 1)
		return (1);
	if (data->token[data->token_nb - 1].type >= 2)
		return (0);
	while (i < data->token_nb)
	{
		if (data->token[i].redir)
			if (!check_after_red(data, i))
				return (0);
		if (data->token[i].type == PIPE)
			if (!check_after_pipe(data, i))
				return (0);
		i++;
	}
	return (1);
}
