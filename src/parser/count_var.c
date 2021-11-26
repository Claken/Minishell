/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 21:27:15 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/22 00:47:34 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	not_a_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	var_first_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (1);
	return (0);
}

int	ft_var_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || (c == '_'))
		return (1);
	return (0);
}

void	norm_count_var(const char *str, int *i, int *nb)
{
	(*i)++;
	if (ft_var_char(str[(*i)]) && !not_a_num(str[(*i)]))
	{
		while (str[(*i)] && ft_var_char(str[(*i)]))
			(*i)++;
		(*nb)++;
	}
	else
	{
		while (str[(*i)] && str[(*i)] != ' ' && str[(*i)] != '$'
			&& str[(*i)] != '\'' && str[(*i)] != '\"')
			(*i)++;
		(*nb)++;
	}
}

int	count_tab_var(const char *s)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] == '$')
			norm_count_var(s, &i, &nb);
		else if (s[i] == '\"' || s[i] == '\'')
		{
			i++;
			nb++;
		}
		else
		{
			while (s[i] && s[i] != '$' && s[i] != '\'' && s[i] != '\"')
				i++;
			nb++;
		}
	}
	return (nb);
}
