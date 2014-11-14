# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/08/11 16:10:24 by bbecker           #+#    #+#              #
#    Updated: 2014/11/10 08:41:01 by bbecker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

F = ./srcs/

I = ./includes/

TOMAKE =	$(F)ft_atoi.c		\
			$(F)ft_isalpha.c	\
			$(F)ft_isprint.c	\
			$(F)ft_memcmp.c		\
			$(F)ft_memset.c		\
			$(F)ft_putstr.c		\
			$(F)ft_strcmp.c		\
			$(F)ft_strncmp.c	\
			$(F)ft_strrchr.c	\
			$(F)ft_toupper.c	\
			$(F)ft_bzero.c		\
			$(F)ft_isascii.c	\
			$(F)ft_memccpy.c	\
			$(F)ft_memcpy.c		\
			$(F)ft_putchar.c	\
			$(F)ft_strcat.c		\
			$(F)ft_strcpy.c		\
			$(F)ft_strlen.c		\
			$(F)ft_strncpy.c	\
			$(F)ft_strstr.c		\
			$(F)ft_isalnum.c	\
			$(F)ft_isdigit.c	\
			$(F)ft_memchr.c		\
			$(F)ft_memmove.c	\
			$(F)ft_putnbr.c		\
			$(F)ft_strchr.c		\
			$(F)ft_strdup.c		\
			$(F)ft_strncat.c	\
			$(F)ft_strlcat.c	\
			$(F)ft_strnstr.c	\
			$(F)ft_tolower.c	\
			$(F)ft_isblank.c	\
			$(F)ft_memdel.c		\
			$(F)ft_strcrl.c		\
			$(F)ft_strequ.c		\
			$(F)ft_striteri.c	\
			$(F)ft_strmap.c		\
			$(F)ft_strnequ.c	\
			$(F)ft_strsplit.c	\
			$(F)ft_strtrim.c	\
			$(F)ft_memalloc.c	\
			$(F)ft_strclr.c		\
			$(F)ft_strdel.c		\
			$(F)ft_striter.c	\
			$(F)ft_strjoin.c	\
			$(F)ft_strmapi.c	\
			$(F)ft_strnew.c		\
			$(F)ft_strsub.c		\
			$(F)ft_itoa.c		\
			$(F)ft_putchar_fd.c	\
			$(F)ft_putendl.c	\
			$(F)ft_putendl_fd.c	\
			$(F)ft_putnbr_fd.c	\
			$(F)ft_putstr_fd.c
TOLIB	=	ft_atoi.o			\
			ft_isalpha.o		\
			ft_isprint.o		\
			ft_memcmp.o			\
			ft_memset.o			\
			ft_putstr.o			\
			ft_strcmp.o			\
			ft_strncmp.o		\
			ft_strrchr.o		\
			ft_toupper.o		\
			ft_bzero.o			\
			ft_isascii.o		\
			ft_memccpy.o		\
			ft_memcpy.o			\
			ft_putchar.o		\
			ft_strcat.o			\
			ft_strlcat.o		\
			ft_strcpy.o			\
			ft_strlen.o			\
			ft_strncpy.o		\
			ft_strstr.o			\
			ft_isalnum.o		\
			ft_isdigit.o		\
			ft_memchr.o			\
			ft_memmove.o		\
			ft_putnbr.o			\
			ft_strchr.o			\
			ft_strdup.o			\
			ft_strncat.o		\
			ft_strnstr.o		\
			ft_tolower.o		\
			ft_isblank.o		\
			ft_memdel.o			\
			ft_strcrl.o			\
			ft_strequ.o			\
			ft_striteri.o		\
			ft_strmap.o			\
			ft_strnequ.o		\
			ft_strsplit.o		\
			ft_strtrim.o		\
			ft_memalloc.o		\
			ft_strclr.o			\
			ft_strdel.o			\
			ft_striter.o		\
			ft_strjoin.o		\
			ft_strmapi.o		\
			ft_strnew.o			\
			ft_strsub.o			\
			ft_itoa.o			\
			ft_putchar_fd.o		\
			ft_putendl.o		\
			ft_putendl_fd.o		\
			ft_putnbr_fd.o		\
			ft_putstr_fd.o

all: $(NAME)

$(NAME):
	gcc -c -Wall -Werror -Wextra $(TOMAKE) -I$(I)
	ar rc $(NAME) $(TOLIB)
	ranlib $(NAME)

clean :
	/bin/rm -rf $(TOLIB) 

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
