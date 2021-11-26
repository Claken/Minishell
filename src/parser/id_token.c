/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 08:10:41 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/19 15:16:22 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_strs(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != NULL)
		i++;
	return (i);
}

void	id_double_char(t_data *data, int i, char **ind_token)
{
	if (!ft_strncmp(ind_token[i], ">>", 2))
		data->token[i].type = RED_DOUT;
	if (!ft_strncmp(ind_token[i], "<<", 2))
		data->token[i].type = RED_DIN;
}

void	id_token(t_data *data, char **ind_token)
{
	int	nb;
	int	i;

	i = -1;
	nb = 0;
	nb = count_strs(ind_token);
	data->token = malloc(sizeof(t_token) * nb + 1);
	while (++i < nb)
	{
		init_token(&data->token[i]);
		data->token[i].type = WORD;
		data->token[i].str = ft_strdup(ind_token[i]);
		data->token[i].index = i;
		if (ft_strlen(ind_token[i]) == 1 && ind_token[i][0] == '|')
			data->token[i].type = PIPE;
		else if (ft_strlen(ind_token[i]) == 2)
			id_double_char(data, i, ind_token);
		else if (ft_strlen(ind_token[i]) == 1 && ind_token[i][0] == '<')
			data->token[i].type = RED_IN;
		else if (ft_strlen(ind_token[i]) == 1 && ind_token[i][0] == '>')
			data->token[i].type = RED_OUT;
		if (data->token[i].type >= 61 && data->token[i].type <= 64)
			data->token[i].redir = 1;
	}
}
