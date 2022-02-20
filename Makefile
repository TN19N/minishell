# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 14:18:57 by mannouao          #+#    #+#              #
#    Updated: 2022/02/20 21:16:26 by mannouao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_SRCS = ./srces/
NAME = minishell
SRCS = $(PATH_SRCS)minishell.c \
		$(PATH_SRCS)errors.c \
		$(PATH_SRCS)execute.c \
		$(PATH_SRCS)mini_tools_1.c \
		$(PATH_SRCS)mini_tools_2.c \
		$(PATH_SRCS)tokens.c \
		$(PATH_SRCS)mini_cmds.c \
		$(PATH_SRCS)init_tokens.c \
		$(PATH_SRCS)get_cmd_paths.c \
		$(PATH_SRCS)her_doc.c \
		$(PATH_SRCS)mini_tools_3.c \
		$(PATH_SRCS)builtins_cmds1.c \
		$(PATH_SRCS)builtins_cmds2.c \
		$(PATH_SRCS)mini_tools_4.c \
		$(PATH_SRCS)cd_cmd.c \
		$(PATH_SRCS)mini_tools_5.c \
		$(PATH_SRCS)echo_cmd.c \
		$(PATH_SRCS)mini_tools_6.c \
		$(PATH_SRCS)export.c

LIBFT_PATH = libft/libft.a
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -L/Users/mannouao/.brew/opt/readline/lib -I/Users/mannouao/.brew/opt/readline/include $(LIBFT_PATH) -o $(NAME)

$(LIBFT_PATH) : 
	make -C libft

./srces/%.o:%.c
	$(CC) $(CFLAGS) -c $<

clean :
	make -C libft clean
	rm -f $(OBJS)

fclean : clean
	make -C libft fclean
	rm -f $(NAME)

re : fclean all