# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
<<<<<<< HEAD
#    Created: 2022/02/14 14:18:57 by mannouao          #+#    #+#              #
#    Updated: 2022/02/14 16:33:14 by mannouao         ###   ########.fr        #
=======
#    Created: 2022/01/31 10:17:04 by mannouao          #+#    #+#              #
#    Updated: 2022/02/14 11:35:54 by hnaciri-         ###   ########.fr        #
>>>>>>> bebae7780885a6bc7f7933897317bbd13ff9f4de
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = minishell.c \
		errors.c \
		execute.c \
		mini_tools_1.c \
		mini_tools_2.c \
		tokens.c \
		mini_cmds.c \
		init_tokens.c \
		get_cmd_paths.c \
		her_doc.c \
		mini_tools_3.c \
<<<<<<< HEAD
		builtins_cmds1.c \
		builtins_cmds2.c
=======
		commands1.c \
		commands2.c
>>>>>>> bebae7780885a6bc7f7933897317bbd13ff9f4de

LIBFT_PATH = libft/libft.a
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lreadline -L/Users/mannouao/.brew/opt/readline/lib -I/Users/mannouao/.brew/opt/readline/include

all : $(NAME)

$(NAME) :
	@make -C libft
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT_PATH) -o $(NAME)


clean :
	@make -C libft fclean
	@rm -f $(NAME)

fclean : clean

re : fclean all