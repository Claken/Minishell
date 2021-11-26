/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_nb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:37:54 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/26 17:08:08 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	add_word(const char *line, int *index, int nb)
{
	while (line[*index] && break_char(line[*index]) == 0)
	{
		if (line[*index] == '\'' || line[*index] == '\"')
		{
			if (!add_quote(line, index, line[*index]))
			{
				printf("minishell: syntax error missing quote\n");
				return (-2);
			}
		}
		(*index)++;
	}
	nb++;
	return (nb);
}

static int	add_pipe_var(const char *line, int *index, int nb)
{
	if (line[*index] == '|')
		(*index)++;
	else if (line[*index] == '$')
	{
		(*index)++;
		while (line[*index] && break_char(line[*index]) == 0)
			(*index)++;
	}
	nb++;
	return (nb);
}

static int	redir_extra(const char *line, int *index, char a, char b)
{
	(*index)++;
	if (line[*index] == b)
	{
		printf("minishell: syntax error near unexpected token `%c'\n",
			line[*index]);
		return (-2);
	}
	else if (line[*index] == a)
		(*index)++;
	if (line[*index] == a || line[*index] == b)
	{
		printf("minishell: syntax error near unexpected token `%c'\n",
			line[*index]);
		return (-2);
	}
	return (1);
}

static int	add_redir(const char *line, int *index, int nb)
{
	int	i;

	i = 42;
	if (line[*index] == '<')
		i = redir_extra(line, index, '<', '>');
	else if (line[*index] == '>')
		i = redir_extra(line, index, '>', '<');
	if (i == -2)
		return (-2);
	return (nb + 1);
}

int	token_nb(const char *line)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] && line[i] != '$' && !break_char(line[i]))
			nb = add_word(line, &i, nb);
		else if (line[i] && (line[i] == '|' || line[i] == '$'))
			nb = add_pipe_var(line, &i, nb);
		else if (line[i] && (line[i] == '<' || line[i] == '>'))
			nb = add_redir(line, &i, nb);
		if (nb == 0 || nb == -2)
			break ;
	}
	return (nb);
}
