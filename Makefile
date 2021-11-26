# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 22:05:09 by earruaba          #+#    #+#              #
#    Updated: 2021/11/24 19:51:50 by sachouam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g3

LIBR =	/home/linuxbrew/.linuxbrew/opt/readline/lib
LIBI =	/home/linuxbrew/.linuxbrew/opt/readline/include

INC			=	-I ./inc #-I $(LIBR) -I $(LIBI)

HEADER		=	./inc/minishell.h
LIBFT		=	libft/libft.a #-L $(LIBR)
LIBFT_DIR	=	libft

SRC			=	src/main.c \
				src/parser/count_utils.c \
				src/parser/count_var.c \
				src/parser/create_token.c \
				src/parser/expand_var_heredoc.c \
				src/parser/expand_var_utils_1.c \
				src/parser/expand_var_utils_2.c \
				src/parser/expand_var.c \
				src/parser/extract_var.c \
				src/parser/id_command_utils.c \
				src/parser/id_token.c \
				src/parser/init.c \
				src/parser/lexer.c \
				src/parser/param_token.c \
				src/parser/parser.c \
				src/parser/quote_var.c \
				src/parser/remove_quotes_utils.c \
				src/parser/remove_quotes.c \
				src/parser/syntax_error.c \
				src/parser/token_nb.c \
				src/free.c \
				src/test_print.c \
				src/get_path.c \
				src/exec/execute_line.c \
				src/exec/errors_handling_exec.c \
				src/exec/heredoc.c \
				src/exec/redirections.c \
				src/exec/about_pipes.c \
				src/exec/exec_cmd_and_builtins.c \
				src/exec/settings.c \
				src/exec/wait_processes.c \
				src/exec/functions_to_spot_tokens.c \
				src/parser/check_valid_command.c \
				src/signals/handle_signals.c \
				src/handle_global.c \
				src/builtins/echo.c \
				src/builtins/env.c \
				src/builtins/pwd.c \
				src/builtins/cd.c \
				src/builtins/export.c \
				src/builtins/unset.c \
				src/builtins/exit.c \
				src/builtins/functions_for_builtin.c \
				src/functions_for_env_01.c \
				src/functions_for_env_02.c \
				src/print_error_message.c \
				src/update_exit_status.c \

OBJ			=	$(SRC:%.c=%.o)

all:		obj $(NAME)

$(NAME):	$(OBJ) $(HEADER)
			@make -C $(LIBFT_DIR)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(INC) -lreadline

obj:
			@mkdir -p obj

obj/%.o:	src/%.c
			@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
			@rm -rf $(OBJ) obj
			@make clean -C $(LIBFT_DIR)

fclean:		clean
			@rm -rf $(NAME)
			@make fclean -C $(LIBFT_DIR)

re:			fclean all

.PHONY:		all clean fclean re
