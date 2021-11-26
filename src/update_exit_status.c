/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 05:27:41 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/24 05:36:51 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void
	update_exit_status(int ret, t_data *data)
{
	char	*update;
	char	*reta;

	update = ft_substr(data->env[0], 0, 2);
	if (!update)
		return ;
	reta = ft_itoa(ret);
	if (!reta)
		return ;
	update = ft_strjoin_free(update, reta);
	if (!update)
		return ;
	if (!join_or_replace(update, data->env, 1))
		return ;
	if (reta)
		free_line(&reta);
	if (update)
		free_line(&update);
}
