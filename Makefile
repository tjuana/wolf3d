# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drafe <drafe@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 11:40:58 by tjuana            #+#    #+#              #
#    Updated: 2020/01/10 21:56:37 by drafe            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

FLAGS =  -O -O0 -O1 -O2 -O3 -Os -g -Wall -Werror -Wextra

CC = gcc

LIBRARIES = -lft -L$(LIBFT_DIRECTORY)\
	-lSDL2 -lSDL2main -L/Users/drafe/.brew/Cellar/sdl2/2.0.10/lib\
	-lSDL2_ttf -L/Users/drafe/.brew/Cellar/sdl2_ttf/2.0.15/lib\
	-lSDL2_image -L/Users/drafe/.brew/Cellar/sdl2_image/2.0.5/lib

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS)\
	
LIBFT = $(addprefix $(LIBFT_DIRECTORY),libft.a)

LIBFT_DIRECTORY = ./libft/

LIBFT_HEADERS = ./libft/includes

HEADERS_DIRECTORY = ./includes/

HEADERS_LIST = wolf3d.h\
	help.h\
	constants.h\
	engine.h\
	events.h\
	player.h\
	wolf3d.h

HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

DIRECTORY = $(shell pwd)

SRCS_DIRECTORY = ./src/

SRCS_LIST = functions_main.c\
			math_functions.c\
			engine_exp.c\
			engine.c\

OBJS_DIRECTORY = objects/

OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))

OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))

LIBFT = libft/libft.a

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIRECTORY) $(OBJS)
	$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"
	
$(OBJS_DIRECTORY):
	@mkdir -p $(OBJS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJS_DIRECTORY) was created$(RESET)"

$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

dd:
	rm $(NAME)

fclean: clean
	@rm -rf $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
	@echo "$(SDL_MAKE): $(RED)was unistalled$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
