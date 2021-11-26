/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:44:09 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/24 01:07:36 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i] != NULL)
		printf("var[%d]=[%s]\n", i, strs[i]);
}

void	print_export(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i] != NULL)
		printf("%s\n", strs[i]);
}
