/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 22:00:25 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/22 20:39:26 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void
	handle_sigint(int s)
{
	int	*pid;

	(void)s;
	pid = ft_return_global();
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (*pid < 1000)
	{
		rl_redisplay();
	}
	*pid = 2;
}

void
	sigint_for_heredoc(int s)
{
	int	*var;

	var = ft_return_global();
	if (s == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		*var = 2;
		close(STDIN_FILENO);
	}
}

void
	sigint_return_status(t_data *data)
{
	int	*ret;

	ret = ft_return_global();
	update_exit_status(130, data);
	*ret = 0;
}

void
	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void
	line_null_so_bye(t_data *data)
{
	write(STDOUT_FILENO, "exit\n", 5);
	data = free_data(data);
	exit(0);
}
