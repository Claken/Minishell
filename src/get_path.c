/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:59:22 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/21 00:01:00 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_path(t_data *data)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", data->env[i], ft_strlen("PATH")) != 0)
		i++;
	if (ft_strncmp("PATH", data->env[i], ft_strlen("PATH")) == 0)
		data->path = ft_split(data->env[i] + 5, ":");
}
