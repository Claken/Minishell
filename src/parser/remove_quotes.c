/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 21:33:46 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/22 20:18:58 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*rm_q(char *str, int qone, int qtwo)
{
	int		i;
	int		j;
	char	*wq;

	i = 0;
	j = 0;
	wq = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!wq)
		return (NULL);
	while (str[i])
	{
		if (i == qone || i == qtwo)
			i++;
		else
		{
			wq[j] = str[i];
			j++;
			i++;
		}
	}
	wq[j] = '\0';
	return (wq);
}

void	norm_find_q(t_data *data, int k, int a, int b)
{
	char	*tmp;

	tmp = rm_q(data->token[k].str, a, b);
	free_line(&data->token[k].str);
	data->token[k].str = ft_strdup(tmp);
	free_line(&tmp);
}

void	valid_not_quote(t_data *data, int k, int *i)
{
	if (data->token[k].str[(*i)] && (data->token[k].str[(*i)] != '\"'
			&& data->token[k].str[(*i)] != '\''))
	(*i)++;
}

static void	find_q(t_data *data, int k, int a, int b)
{
	int		i;

	i = 0;
	while (data->token[k].str[i])
	{
		if (data->token[k].str[i] == '\"' || data->token[k].str[i] == '\'')
		{
			a = i;
			i++;
			while (data->token[k].str[i])
			{
				if (data->token[k].str[i] == data->token[k].str[a])
				{
					b = i;
					norm_find_q(data, k, a, b);
					if (ft_strlen(data->token[k].str) == 0)
						return ;
					i--;
					break ;
				}
				i++;
			}
		}
		valid_not_quote(data, k, &i);
	}
}

void	remove_quotes(t_data *data)
{
	int	i;
	int	q[2];

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (i < data->token_nb)
	{
		if (data->token[i].type == WORD && is_quote(data, i))
			find_q(data, i, q[0], q[1]);
		i++;
	}
}
