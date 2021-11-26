/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:14:19 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/26 17:07:59 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	empty_line(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void
	loop_rl(t_data *data, char *line)
{
	int	*var;

	var = ft_return_global();
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			line = readline("minishell$ ");
		if (*var == 2)
			sigint_return_status(data);
		if (!line)
			line_null_so_bye(data);
		if (parse_line(data, line))
		{
			if (data->token_nb > 0)
				execute_line(data);
		}
		free_token(data);
		if (!empty_line(line))
			add_history(line);
		free_line(&line);
	}
}

void
	*init_env(t_data *data, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 2));
	if (!data->env)
		return (NULL);
	i = 1;
	data->env[0] = ft_strdup("?=0");
	while (env[j] != NULL)
	{
		data->env[i] = ft_strdup(env[j]);
		i++;
		j++;
	}
	data->env[i] = NULL;
	return (data->env);
}

void	*init_no_env(t_data *d)
{
	d->env = malloc(sizeof(char *) * 3);
	if (!d->env)
		return (NULL);
	d->env[0] = ft_strdup("?=");
	d->env[1] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:");
	d->env[1] = ft_strjoin_free(d->env[1], "/usr/sbin:/usr/bin:/sbin:/bin");
	d->env[2] = NULL;
	return (d->env);
}

int
	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	*data;

	(void)argc;
	(void)argv;
	line = NULL;
	g_global = 0;
	handle_signals();
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_data(data);
	if (count_strs(env) > 0)
	{
		init_env(data, env);
		get_path(data);
	}
	else
		init_no_env(data);
	loop_rl(data, line);
	return (0);
}
