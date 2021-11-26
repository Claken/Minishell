/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:26:27 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/24 05:35:51 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void
	handle_line_here(char *line, int *var)
{
	if (!line && *var != 2)
		ft_print_error_message(NULL, NULL,
			"warning: here-document delimited by end-of-line");
	free_line(&line);
}

static int
	zero_if_sigint(int hdp[], int *fd, int *var)
{
	*var = 0;
	close(hdp[0]);
	close(hdp[1]);
	dup2(*fd, STDIN_FILENO);
	close(*fd);
	signal(SIGINT, handle_sigint);
	return (0);
}

static int
	one_if_its_all_good(int hdp[], t_data *data, int curr, int *fd)
{
	if (data->token[curr].in != STDIN_FILENO)
		close(data->token[curr].in);
	data->token[curr].in = hdp[0];
	close(hdp[1]);
	close(*fd);
	signal(SIGINT, handle_sigint);
	return (1);
}

int
	ft_heredoc(char *eof, t_data *data, int curr, int quote)
{
	int		hdp[2];
	char	*line;
	int		*var;
	int		fd;

	if (pipe(hdp) < 0)
		return (0);
	signal(SIGINT, &sigint_for_heredoc);
	var = ft_return_global();
	fd = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, eof))
			break ;
		if (!quote && is_var(line) != -1)
			line = expand_var_heredoc(data, line);
		write(hdp[1], line, ft_strlen(line));
		write(hdp[1], "\n", 1);
		free_line(&line);
	}
	handle_line_here(line, var);
	if (*var == 2)
		return (zero_if_sigint(hdp, &fd, var));
	return (one_if_its_all_good(hdp, data, curr, &fd));
}
