# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/08 15:08:34 by bbecker           #+#    #+#              #
#    Updated: 2014/12/22 17:20:44 by bbecker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

F = ./srcs/

I = -I./headers

L = -L./lib -lft

TOMAKE =	$(F)ft_ls.c				\
			$(F)ft_free.c			\
			$(F)ft_arg.c			\
			$(F)ft_error.c			\
			$(F)ft_lsttools.c		\
			$(F)ft_sort.c			\
			$(F)ft_checktype.c		\
			$(F)ft_recursive.c		\
			$(F)maxsize.c			\
			$(F)ft_stats.c			\
			$(F)print.c				\
			$(F)majmin.c			\
			$(F)printlong1.c		\
			$(F)printlong2.c		\
			$(F)directorystuff.c	\
			$(F)readandwrite.c

TOLIB	=	ft_ls.o				\
			ft_free.o			\
			ft_arg.o			\
			ft_error.o			\
			ft_lsttools.o		\
			ft_sort.o			\
			ft_checktype.o		\
			ft_recursive.o		\
			maxsize.o			\
			ft_stats.o			\
			print.o				\
			majmin.o			\
			printlong1.o		\
			printlong2.o		\
			directorystuff.o	\
			readandwrite.o


all: $(NAME)

$(NAME):
	make -C ./lib/libft
	gcc -c -Wall -Werror -Wextra $(TOMAKE) $(I) $(L)
	gcc -Wall -Werror -Wextra $(I) $(L) -o $(NAME) $(TOLIB)

clean :
	/bin/rm -rf $(TOLIB)

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./lib/libft clean

cleanlib:
	make -C ./lib/libft fclean

re: fclean all

relib:
	make -C ./lib/libft re

.PHONY: clean fclean cleanlib re relib all
