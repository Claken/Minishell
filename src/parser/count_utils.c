/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:39:05 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/12 20:13:45 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	break_char(char c)
{
	if (c == ' ' || c == '\t' || c == '|'
		|| c == '<' || c == '>' || c == '\0')
		return (1);
	return (0);
}

/*
** making sure that I've a quote to make a pair
** return 0 if not
*/

int	add_quote(const char *line, int *index, char quote)
{
	(*index)++;
	while (line[*index] != '\0' && line[*index] != quote)
		(*index)++;
	if (line[*index] == '\0')
		return (0);
	return (1);
}
