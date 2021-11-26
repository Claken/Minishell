/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:10:18 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/04 16:46:20 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int
	ft_pwd(void)
{
	char	buf[255];
	int		ret;

	ret = 0;
	if (!getcwd(buf, sizeof(buf)))
	{
		ft_print_error_message("pwd", NULL, strerror(errno));
		ret = 1;
	}
	else
		printf("%s\n", buf);
	return (ret);
}
