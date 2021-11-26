/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 21:25:54 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/22 00:01:16 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*extract_not_var(const char *str, int *i)
{
	int		j;
	char	*var;
	int		index;

	index = 0;
	j = (*i) + 1;
	while (str[j] && str[j] != '$' && str[j] != '\"' && str[j] != '\'')
		j++;
	var = malloc(sizeof(char) * (j - (*i) + 1) + 1);
	while ((*i) < j)
	{
		var[index] = str[(*i)];
		(*i)++;
		index++;
	}
	var[index] = '\0';
	return (var);
}

char	*extract_invalid_var(const char *str, int *i)
{
	int		j;
	char	*var;
	int		index;

	index = 0;
	j = (*i) + 1;
	while (str[j] && str[j] != ' ' && str[j] != '$')
		j++;
	var = malloc(sizeof(char) * (j - (*i) + 1) + 1);
	while ((*i) < j)
	{
		var[index] = str[(*i)];
		(*i)++;
		index++;
	}
	var[index] = '\0';
	return (var);
}

char	*extract_valid_var(const char *str, int *i)
{
	int		j;
	char	*var;
	int		index;

	index = 0;
	j = (*i) + 1;
	while (str[j] && ft_var_char(str[j]))
		j++;
	var = malloc(sizeof(char) * (j - (*i) + 1) + 1);
	while ((*i) < j)
	{
		var[index] = str[(*i)];
		(*i)++;
		index++;
	}
	var[index] = '\0';
	return (var);
}
