/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:41:25 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/26 17:08:06 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	absolute_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (1);
	return (0);
}

void	norm_id(t_data *d, int i)
{
	d->token[i].cmd.cmd = ft_strdup(d->token[i].str);
	d->token[i].cmd.exist = 1;
}

void	id_command(t_data *d, int i)
{
	while (++i < d->token_nb)
	{
		init_cmd(&d->token[i].cmd);
		if (absolute_path(d->token[i].str))
			norm_id(d, i);
		else if (d->token[i].type == WORD)
		{
			if (builtin_fct(d->token[i].str))
			{
				d->token[i].cmd.cmd = ft_strdup(d->token[i].str);
				if (!d->token[i].cmd.cmd)
					return ;
				builtin_exist(&d->token[i].cmd);
			}
			else if (path_exist(d->env) && other_fct(d->token[i].str, d->env))
			{
				d->token[i].cmd.cmd = ft_paths(d->token[i].str, d->env);
				if (!d->token[i].cmd.cmd)
					return ;
				d->token[i].cmd.exist = 1;
			}
		}
	}
}

int	parse_line(t_data *data, char *line)
{
	int	i;

	i = -1;
	if (lexer(data, line))
	{
		if (syntax_doublon(data) && check_valid_command(data))
		{
			expand_var(data);
			remove_quotes(data);
			id_command(data, i);
			param_token(data);
			return (1);
		}
		else
		{
			printf("minishell: syntax error\n");
			update_exit_status(2, data);
		}
	}
	return (0);
}
