/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 02:21:14 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/22 02:22:04 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*var_quote(char c)
{
	char	*quote;

	quote = malloc(sizeof(char) * 2);
	if (!quote)
		return (NULL);
	quote[0] = c;
	quote[1] = '\0';
	return (quote);
}

static void	or_not_norm(char **var, int *i, char c, int end)
{
	while (++(*i) < end && var[(*i)][0] != c)
		;
	if (var[(*i)][0] == c)
		(*i)++;
}

int	exp_or_not(char **var, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (var[i][0] == '\"')
		{
			or_not_norm(var, &i, '\"', end);
			if (i == end)
				return (1);
		}
		if (var[i][0] == '\'')
		{
			or_not_norm(var, &i, '\'', end);
			if (i == end)
				return (0);
		}
		if (i == end)
			return (1);
		i++;
	}
	return (1);
}

int	char_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}
