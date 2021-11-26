/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_to_spot_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 05:18:21 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/24 23:35:45 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int
	check_type_in_command(t_data *data, int whattype, int curr, int j)
{
	int	i;

	i = curr;
	while (i <= j)
	{
		if (whattype == REDIR)
		{
			if (data->token[i].redir == 1)
				return (i);
		}
		else if (data->token[i].type == whattype)
			return (i);
		i++;
	}
	return (-1);
}

int
	find_the_command(t_data *data, int curr, int last)
{
	int	i;

	i = curr - 1;
	while (++i <= last)
	{
		if (data->token[i].type == WORD)
		{
			if (i - 1 < 0 || data->token[i - 1].redir == 0)
			{
				if (ft_strlen(data->token[i].str) > 0)
					return (i);
			}
		}
	}
	return (-1);
}

int
	check_type(t_data *data, int whattype)
{
	int	i;

	i = -1;
	while (++i < data->token_nb)
	{
		if (whattype == REDIR)
		{	
			if (data->token[i].redir == 1)
				return (i);
		}
		else if (data->token[i].type == whattype)
			return (i);
	}
	return (-1);
}
