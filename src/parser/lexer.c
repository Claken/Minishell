/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:44:48 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/26 17:08:32 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	lexer(t_data *data, char *line)
{
	char	**ind_token;
	int		k;

	k = 0;
	data->token_nb = token_nb(line);
	if (data->token_nb > 0)
	{
		ind_token = create_token(line, data->token_nb, k);
		if (!ind_token)
			return (0);
		id_token(data, ind_token);
		ind_token = free_ind(ind_token);
		return (1);
	}
	else if (data->token_nb < 0)
	{
		update_exit_status(2, data);
	}
	return (0);
}
