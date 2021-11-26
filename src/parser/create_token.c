/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:52:42 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/21 19:18:29 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	co_quote(const char *str, int *i, char quote)
{
	(*i)++;
	while (str[(*i)] != '\0' && str[(*i)] != quote)
		(*i)++;
	if (str[(*i)] == '\0')
		return (0);
	return (1);
}

static char	*co_pipe_var(const char *str, int *i)
{
	int	start;

	if (str[(*i)] == '|')
		return (ft_strdup("|"));
	else if (str[(*i)] == '$')
	{
		start = (*i);
		while (str[(*i)] && break_char(str[(*i)]) == 0)
			(*i)++;
		return (ft_substr(str, start, ((*i) - start)));
	}
	return (NULL);
}

static char	*co_word(const char *str, int *i)
{
	int	start;

	start = (*i);
	while (str[(*i)] && break_char(str[(*i)]) == 0)
	{
		if (str[(*i)] == '\'' || str[(*i)] == '\"')
		{
			if (!co_quote(str, i, str[(*i)]))
				return (NULL);
		}
		(*i)++;
	}
	return (ft_substr(str, start, ((*i) - start)));
}

static char	*co_redir(const char *str, int *i)
{
	if (str[(*i)] == '<' && str[(*i) + 1] == '<')
	{
		(*i)++;
		return (ft_strdup("<<"));
	}
	else if (str[(*i)] == '>' && str[(*i) + 1] == '>')
	{
		(*i)++;
		return (ft_strdup(">>"));
	}
	else if (str[(*i)] == '<')
		return (ft_strdup("<"));
	else if (str[(*i)] == '>')
		return (ft_strdup(">"));
	return (NULL);
}

char	**create_token(const char *str, int nb, int k)
{
	char	**tok;
	int		i;

	i = -1;
	tok = malloc(sizeof(char *) * (nb + 1));
	if (!tok)
		return (NULL);
	while (str[++i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] && str[i] != '$' && !break_char(str[i]))
		{
			tok[k++] = co_word(str, &i);
			i--;
		}
		else if (str[i] && (str[i] == '|' || str[i] == '$'))
			tok[k++] = co_pipe_var(str, &i);
		else if (str[i] && (str[i] == '<' || str[i] == '>'))
			tok[k++] = co_redir(str, &i);
		if (!str[i])
			break ;
	}
	tok[k] = NULL;
	return (tok);
}
