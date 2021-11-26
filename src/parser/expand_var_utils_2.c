/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:13:35 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/19 19:15:51 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*replace_var(t_data *data, int j)
{
	char	*tmp;

	tmp = ft_strdup(data->env[j] + egal_pos(data->env[j]) + 1);
	return (tmp);
}

char	**tab_var(char *str)
{
	int		i;
	char	**var;

	i = -1;
	while (str[++i] != '$')
		;
	var = ft_split(str + i, "$");
	return (var);
}

char	*join_var(char *token_str, char **var)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (var[i] != NULL)
	{
		str = ft_strjoin_free(str, var[i]);
		i++;
	}
	if (token_str != NULL)
		free_line(&token_str);
	token_str = ft_strdup(str);
	if (str != NULL)
		free_line(&str);
	return (token_str);
}
