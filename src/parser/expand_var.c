/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:51:23 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/25 02:07:13 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**split_var(const char *str)
{
	int		i;
	char	**var;
	int		k;

	i = 0;
	k = 0;
	var = malloc(sizeof(char *) * (count_tab_var(str) + 1));
	if (!var)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (ft_var_char(str[i + 1]) && !not_a_num(str[i + 1]))
				var[k++] = extract_valid_var(str, &i);
			else
				var[k++] = extract_invalid_var(str, &i);
		}
		else if (str[i] == '\'' || str[i] == '\"')
			var[k++] = var_quote(str[i++]);
		else
			var[k++] = extract_not_var(str, &i);
	}
	var[k] = NULL;
	return (var);
}

int	condi_var(char *str, char *env)
{
	if (ft_strncmp(str + 1, env, ft_strlen(str + 1)) == 0
		&& ft_strncmp(str + 1, env, egal_pos(env)) == 0)
		return (1);
	return (0);
}

char	*search_var_norm(char *str, int j, t_data *d)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strlen(str) > 1 && str[0] == '$')
	{
		if (condi_var(str, d->env[j]))
			return (replace_var(d, j));
		else if (j + 1 == count_strs(d->env) && !condi_var(str, d->env[j]))
			return (not_a_var(str));
		else if (j + 1 == count_strs(d->env)
			&& !condi_var(str, d->env[j]) && var_first_char(str[1]))
			return (not_a_var(str));
	}
	else
		return (not_a_var(str));
	return (NULL);
}

char	**search_var(t_data *d, int i, int j, int k)
{
	char	**var;
	char	*tmp;

	tmp = NULL;
	var = split_var(d->token[i].str);
	while (var[++k] != NULL)
	{
		if (!char_is_quote(var[k][0]) && exp_or_not(var, k))
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
	}
	return (var);
}

void	expand_var(t_data *data)
{
	int		i;
	int		j[2];
	char	**var;

	i = 0;
	j[0] = -1;
	j[1] = -1;
	while (i < data->token_nb)
	{
		if (data->token[i].type == WORD)
		{
			if (is_var(data->token[i].str) == 1)
			{
				var = search_var(data, i, j[0], j[1]);
				data->token[i].str = join_var(data->token[i].str, var);
				if (var)
					var = free_ind(var);
			}
		}
		i++;
	}
}
