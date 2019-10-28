# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/03 18:51:09 by tjuana            #+#    #+#              #
#    Updated: 2019/10/28 14:17:51 by tjuana           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_putchar.c ft_putchar_fd.c ft_atoi.c ft_strcmp.c ft_strdup.c \
		ft_strlen.c ft_strstr.c ft_islower.c ft_isupper.c ft_tolower.c \
		ft_toupper.c ft_isprint.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_isalnum.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c \
		ft_strncmp.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
		ft_memmove.c ft_memchr.c ft_memcmp.c ft_strchr.c ft_strrchr.c \
		ft_strlcat.c ft_strnstr.c ft_memalloc.c ft_memdel.c ft_strnew.c \
		ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
		ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
		ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_putendl.c \
		ft_putendl_fd.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_strrev.c \
		ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
		ft_lstmap.c ft_iswsp.c ft_count_words.c ft_swap.c ft_strclen.c \
		ft_strndup.c ft_strcdup.c ft_strnlen.c get_next_line.c \
		ft_intsplitstr.c ft_putdbl.c ft_count_lines.c ft_line_len.c \
		ft_countwords.c ft_lst_rev.c ft_lstcount.c ft_2arrclean.c



OBJECTS = ft_putchar.o ft_putchar_fd.o ft_atoi.o ft_strcmp.o ft_strdup.o \
		ft_strlen.o ft_strstr.o ft_islower.o ft_isupper.o ft_tolower.o \
		ft_toupper.o ft_isprint.o ft_isalpha.o ft_isascii.o ft_isdigit.o \
		ft_isalnum.o ft_strcpy.o ft_strncpy.o ft_strcat.o ft_strncat.o \
		ft_strncmp.o ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o \
		ft_memmove.o ft_memchr.o ft_memcmp.o ft_strchr.o ft_strrchr.o \
		ft_strlcat.o ft_strnstr.o ft_memalloc.o ft_memdel.o ft_strnew.o \
		ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o ft_strmap.o \
		ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o \
		ft_putnbr.o ft_putnbr_fd.o ft_putstr.o ft_putstr_fd.o ft_putendl.o \
		ft_putendl_fd.o ft_strtrim.o ft_strsplit.o ft_itoa.o ft_strrev.o \
		ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o \
		ft_lstmap.o ft_iswsp.o ft_count_words.o ft_swap.o ft_strclen.o \
		ft_strndup.o ft_strcdup.o ft_strnlen.o get_next_line.o \
		ft_intsplitstr.o ft_putdbl.o ft_count_lines.o ft_line_len.o \
		ft_countwords.o ft_lst_rev.o ft_lstcount.o ft_2arrclean.o


INCLUDES=./

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(SRCS) libft.h
	@gcc -Wall -Wextra -Werror -I$(INCLUDES) -c $(SRCS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJECTS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
