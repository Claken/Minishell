/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:11:54 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/25 02:42:50 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

# define UNDEF 0
# define WORD 1
# define PIPE 2
# define REDIR 60
# define RED_OUT 61
# define RED_IN 62
# define RED_DOUT 63
# define RED_DIN 64

# ifdef	__linux__
#  define RET 2
#  define CLEX __O_CLOEXEC
# else
#  define RET 255
#  define CLEX O_CLOEXEC
# endif

static int	g_global;

typedef struct s_collect
{
	int		start;
	int		i;
	int		itoken;
	char	**token;
	char	*s;
}	t_collect;

typedef struct s_cmd
{
	char	*cmd;
	int		builtin;
	int		exist;
}	t_cmd;

typedef struct s_token
{
	char	*str;
	int		index;
	int		type;
	int		redir;
	int		in;
	int		out;
	t_cmd	cmd;
	char	**param;
	int		quotes;
}	t_token;

typedef struct s_data
{
	int		token_nb;
	char	**path;
	char	**env;
	t_token	*token;
}	t_data;

typedef struct s_exec
{
	int		i;
	int		j;
	int		cmd;
	int		checkpipe;
	int		ret;
	pid_t	proid;
}	t_exec;

void	*free_ind(char **ind);
void	free_line(char **line);
void	*free_data(t_data *data);
void	free_token(t_data *data);

void	init_data(t_data *data);
void	init_token(t_token *token);
void	init_cmd(t_cmd *cmd);

void	get_path(t_data *data);

void	print_strs(char **strs);
void	print_export(char **strs);

int		parse_line(t_data *data, char *line);
int		builtin_fct(char *cmd);

int		lexer(t_data *data, char *line);
int		syntax_doublon(t_data *data);

int		token_nb(const char *line);
int		add_quote(const char *line, int *index, char quote);
int		break_char(char c);
int		count_strs(char **str);

char	**create_token(const char *str, int nb, int k);

void	id_token(t_data *data, char **ind_token);

void	expand_var(t_data *data);
char	*not_a_var(char *var);
int		egal_pos(char *str);
int		var_index(char *str);
int		is_var(char *str);
char	*dup_until(char *str, char c);
char	*replace_var(t_data *data, int j);
char	**tab_var(char *str);
char	*join_var(char *token_str, char **var);
int		var_first_char(char c);
char	*ft_paths(char *cmd, char **env);
int		other_fct(char *cmd, char **env);
void	builtin_exist(t_cmd *cmd);
char	*extract_not_var(const char *str, int *i);
char	*extract_invalid_var(const char *str, int *i);
char	*extract_valid_var(const char *str, int *i);
int		not_a_num(char c);
int		var_first_char(char c);
int		ft_var_char(char c);
void	norm_count_var(const char *str, int *i, int *nb);
int		count_tab_var(const char *str);
char	*expand_var_heredoc(t_data *data, char *str);
char	**split_var(const char *str);
char	*search_var_norm(char *str, int j, t_data *d);
int		char_is_quote(char c);
int		exp_or_not(char **var, int end);
char	*var_quote(char c);

void	remove_quotes(t_data *data);
int		is_quote(t_data *data, int k);

void	param_token(t_data *data);

char	**cpy_env(char **envp);
char	*find_var_in_env(char *var, char **env);
int		join_or_replace(char *var, char **env, int boolean);
char	*ft_get_var_in_env(char *var, char **envp);
char	*ft_get_var_name(char *var);
char	*ft_get_var_val_in_env(char *var, char **envp);
int		path_exist(char **envp);

void	ft_print_error_message(char *cmd, char *arg, char *phrase);
void	ft_errors_handling(t_data *data, int curr, int j, int *ret);

int		ft_export(char ***env, char **args);
int		ft_pwd(void);
int		ft_unset(char **args, char ***env, t_data *data);
int		ft_env(char **envp);
int		ft_echo(char **args);
int		ft_cd(char **args, char **envp);
int		ft_exit(char **args, t_data *data);

void	execute_line(t_data *data);

int		exec_builtin(char *built, char ***env, char **arg, t_data *data);

void	handle_sigint(int s);
void	sigint_for_heredoc(int s);
void	handle_signals(void);
void	line_null_so_bye(t_data *data);
void	sigint_return_status(t_data *data);

void	update_exit_status(int ret, t_data *data);

void	*ft_return_global(void);

int		check_valid_command(t_data *data);

int		find_the_command(t_data *data, int curr, int last);
int		check_this_type_two(t_data *data, int whattype, int curr, int j);

int		ft_heredoc(char *eof, t_data *data, int curr, int quote);

int		handle_redirections(t_data *data, int curr, int j, int *fd);
int		handle_double_redir_in(t_data *data, int curr, int j);

int		ft_check_if_pipe(t_data *data, int i, int j, int pi[]);
void	close_pipes(int checkpipe, int pi[]);

int		exec_fork(t_data *data, t_exec *exec, int pi[]);
void	exec_builtin_w_out_pipe(t_data *data, t_exec *exec);

void	close_in_and_out(t_data *data, int curr);

void	set_struct_exec(t_exec *exec);
int		set_delimiter_and_pipe(t_data *data, t_exec *exec, int pi[]);
int		set_in_and_out(t_data *data, int curr, int j, int pi[]);

int		check_type(t_data *data, int whattype);
int		check_type_in_command(t_data *data, int whattype, int curr, int j);
int		find_the_command(t_data *data, int curr, int last);

void	ft_for_waiting(t_exec *exec);

#endif
