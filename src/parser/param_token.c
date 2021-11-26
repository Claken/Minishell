/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:52:29 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/19 21:04:45 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_param(t_data *data, int i)
{
	int	nb;
	int	j;

	nb = 0;
	j = i;
	while (j < data->token_nb && data->token[j].type != PIPE)
	{
		if (j + 1 < data->token_nb && data->token[j].redir == 1)
			j += 2;
		else
		{
			j++;
			nb++;
		}
	}
	return (nb);
}

char	**get_param(t_data *data, int i)
{
	char	**param;
	int		nb_param;
	int		j;

	j = 0;
	nb_param = count_param(data, i);
	param = malloc(sizeof(char *) * (nb_param + 1));
	if (!param)
		return (NULL);
	while (j < nb_param)
	{
		if (i + 1 < data->token_nb && data->token[i].redir == 1)
			i = i + 2;
		if (data->token[i].redir == 0)
		{
			param[j] = ft_strdup(data->token[i].str);
			j++;
			i++;
		}
	}
	param[j] = NULL;
	return (param);
}

void	param_token(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->token_nb)
	{
		if (data->token[i].cmd.exist)
		{
			data->token[i].param = get_param(data, i);
		}
	}
}
