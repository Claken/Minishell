/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 01:33:28 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/26 16:54:39 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_line(char **line)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
}

void	*free_ind(char **ind)
{
	int	i;

	i = -1;
	if (ind)
	{
		while (ind[++i])
			free_line(&ind[i]);
		free(ind);
	}
	return (NULL);
}

void	*free_data(t_data *data)
{
	int	i;

	if (data->path)
		data->path = free_ind(data->path);
	if (data->env)
		data->env = free_ind(data->env);
	i = -1;
	while (++i < data->token_nb)
	{
		if (data->token[i].str)
			free_line(&data->token[i].str);
		if (data->token[i].cmd.exist)
			free_line(&data->token[i].cmd.cmd);
		if (data->token[i].param)
			data->token[i].param = free_ind(data->token[i].param);
	}
	if (data->token)
		free(data->token);
	if (data)
		free(data);
	return (NULL);
}

void	free_token(t_data *data)
{
	int	i;

	i = -1;
	if (data->token_nb > 0)
	{
		while (++i < data->token_nb)
		{
			if (data->token[i].cmd.exist == 1)
			{
				free_line(&data->token[i].cmd.cmd);
				data->token[i].param = free_ind(data->token[i].param);
			}
			if (data->token[i].str != NULL)
				free_line(&data->token[i].str);
		}
	}
	if (data->token)
	{
		free(data->token);
		data->token = NULL;
	}
	data->token_nb = 0;
}
