# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drafe <drafe@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 11:40:58 by tjuana            #+#    #+#              #
#    Updated: 2019/12/18 19:33:55 by drafe            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

FLAGS = -Wall -Werror -Wextra -O -O0 -O1 -O2 -O3 -Os -std=c99 -g

CC = gcc

LIBRARIES = -lft -L$(LIBFT_DIRECTORY)\
	-lSDL2 -lSDL2main -L/Users/drafe/.brew/Cellar/sdl2/2.0.10/lib\
	-lSDL2_ttf -L/Users/drafe/.brew/Cellar/sdl2_ttf/2.0.15/lib

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS)\
	
LIBFT = $(addprefix $(LIBFT_DIRECTORY),libft.a)

LIBFT_DIRECTORY = ./libft/

LIBFT_HEADERS = ./libft/includes

HEADERS_DIRECTORY = ./includes/

HEADERS_LIST = bmp_parser.h\
	constants.h\
	door.h\
	player.h\
	sprites.h\
	wolf3d.h

HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

DIRECTORY = $(shell pwd)

SRCS_DIRECTORY = ./src/

SRCS_LIST = alg_wu_color.c\
			alg_wu_draw.c\
			alg_wu.c\
			animation.c\
			bmp_parser.c\
			check_map.c\
			door.c\
			draw_walls.c\
			fpc.c\
			floor.c\
			help.c\
			enemies_ai.c\
			enemies.c\
			events.c\
			events_exp.c\
			events_mouse.c\
			main.c\
			map.c\
			map_arrow.c\
			move.c\
			player_stats.c\
			putstr_sdl.c\
			ray_casting.c\
			read_map.c\
			sdl.c\
			sdl_error.c\
			sdl_render.c\
			sound.c\
			sprites.c\
			sprites_help.c\
			textures.c\
			threads.c

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
