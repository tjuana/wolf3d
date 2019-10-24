# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 11:40:58 by tjuana            #+#    #+#              #
#    Updated: 2019/10/24 18:55:25 by tjuana           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= wolf3d

# src / obj files
SRC		=	main.c \
			sdl.c \
			help.c \
			read_map.c \
			textures.c \
											

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc -g 
CFLAGS	= -Ofast -flto -march=native

# mlx library
SDL_INC	= -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers
SDL_FRW = -F ~/Library/Frameworks/ 
SDL_LNK = -framework SDL2  


# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft/includes
FT_LNK	= -L ./libft -l ft

# directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

# colors
RED=\033[1;31m
GRE=\033[1;32m
LCY=\033[1;36m
LYE=\033[1;33m
NC=\033[0m

.PHONY: all, clean, fclean, re

all: obj $(FT_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@$(CC) $(CFLAGS) $(SDL_FRW) $(SDL_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<
	@echo "${LCY} ┣╸ ${NC}$<" | sed 's/\.c/\.o/g'

$(FT_LIB):
	@make -C $(FT)
	@echo "${GRE}(✓) Libft${NC}"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(SDL_FRW) $(SDL_LNK) $(FT_LNK) -lm -o $(NAME)
	@echo "${LYE}(✓) $(NAME)"

clean:
	@rm -rf $(OBJDIR)
	@make -C $(FT) clean
	
	@echo "${RED}(✗) Objects${NC}"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(FT) fclean
	@echo "${RED}(✗) $(NAME)${NC}"

re: fclean all
