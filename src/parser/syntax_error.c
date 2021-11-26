/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:35:17 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/16 17:39:14 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	doublon_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->token_nb)
	{
		if (data->token[i].type == PIPE)
		{
			if (i + 1 < data->token_nb)
			{
				if (data->token[i + 1].type == PIPE)
					return (0);
			}
		}
	}
	return (1);
}

static int	doublon_redir(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->token_nb)
	{
		if (data->token[i].redir)
		{
			if (i + 1 < data->token_nb)
			{
				if (data->token[i + 1].redir)
					return (0);
			}
		}
	}
	return (1);
}

int	syntax_doublon(t_data *data)
{
	if (doublon_pipe(data) && doublon_redir(data))
		return (1);
	return (0);
}
