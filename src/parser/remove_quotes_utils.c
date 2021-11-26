/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 20:15:49 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/22 20:20:13 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_quote(t_data *data, int k)
{
	int	i;

	i = 0;
	while (data->token[k].str[i])
	{
		if (data->token[k].str[i] == '\'' || data->token[k].str[i] == '\"')
		{
			data->token[k].quotes = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
