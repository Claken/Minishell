/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 23:56:14 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/21 00:57:52 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*heredoc_var(t_data *d, char *str, int j, int k)
{
	char	**var;
	char	*tmp;

	tmp = NULL;
	var = split_var(str);
	while (var[++k] != NULL)
	{
		j = -1;
		while (d->env[++j] != NULL)
		{
			tmp = search_var_norm(var[k], j, d);
			if (tmp != NULL)
			{
				free_line(&var[k]);
				var[k] = ft_strdup(tmp);
				free_line(&tmp);
				break ;
			}
		}
	}
	tmp = join_var(str, var);
	if (var)
		var = free_ind(var);
	return (tmp);
}

char	*expand_var_heredoc(t_data *data, char *str)
{
	int		i[2];
	char	*tmp;

	i[0] = -1;
	i[1] = -1;
	if (is_var(str) == 1)
	{
		tmp = heredoc_var(data, str, i[0], i[1]);
		return (tmp);
	}
	return (NULL);
}
