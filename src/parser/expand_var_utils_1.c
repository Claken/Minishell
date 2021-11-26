/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:31:15 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/18 20:55:18 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_var(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (1);
	}
	return (-1);
}

int	var_index(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (i);
	}
	return (0);
}

int	egal_pos(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
	}
	return (-1);
}

char	*not_a_var(char *v)
{
	char	*tmp;

	if (v[0] == '$' && ft_strlen(v) > 1)
	{
		if (var_first_char(v[1]))
			tmp = ft_strdup("");
		else
			tmp = ft_strdup(v);
	}
	else
		tmp = ft_strdup(v);
	return (tmp);
}

char	*dup_until(char *str, char c)
{
	int		i;
	char	*until;

	i = 0;
	while (str[i] != c)
		i++;
	until = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] != c)
	{
		until[i] = str[i];
		i++;
	}
	until[i] = '\0';
	return (until);
}
