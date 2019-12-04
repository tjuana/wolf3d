# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 11:40:58 by tjuana            #+#    #+#              #
#    Updated: 2019/12/04 18:10:41 by tjuana           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

FLAGS = -Wall -Werror -Wextra -O -O0 -O1 -O2 -O3 -Os -std=c99 -g
CC = gcc
LIBRARIES = -lft -L$(LIBFT_DIRECTORY) -F SDL2/Frameworks   -lSDL2 -L$(SDL_DIRECTORY) -lSDL2main -L$(SDL_DIRECTORY) -lSDL2-2.0.0 -L$(SDL_DIRECTORY)
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(SDL_HEADERS)

LIBFT = $(addprefix $(LIBFT_DIRECTORY),libft.a)
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = ./libft/includes
SDL_HEADERS = include/

HEADERS_DIRECTORY = ./includes/
HEADERS_LIST =	wolf3d.h \
				player.h \
				door.h \
				constants.h \
				sprites.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

DIRECTORY =  $(shell pwd)

SDL_DIRECTORY = ./lib
SDL_MAKE = ./SDL2

LIB_LIST =	libSDL2.a\
			libSDL2.la\
			libSDL2_test.la\
			libSDL2main.la\
			libSDL2-2.0.0.dylib\
			libSDL2.dylib\
			libSDL2_test.a\
			libSDL2main.a

SRCS_DIRECTORY = ./src/
SRCS_LIST = alg_wu_color.c\
			alg_wu_draw.c\
			alg_wu.c\
			animation.c\
			draw_walls.c\
			floor.c\
			help.c\
			read_map.c\
			events.c\
			events_exp.c\
			events_mouse.c\
			main.c\
			move.c\
			map.c\
			map_arrow.c\
			ray_casting.c\
			sdl.c\
			sdl_error.c\
			sdl_render.c\
			sound.c\
			textures.c\
			threads.c \
			check_map.c \
			sprites.c \
			sprites_help.c

OBJS_DIRECTORY = objects/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))
SDL_LIBS = $(addprefix $(DIRECTORY)/lib/, $(LIB_LIST))

LIBFT = libft/libft.a
LIBSDL_EXIST = 0
err = no

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIRECTORY) $(OBJS)
	$(foreach p,$(SDL_LIBS),$(if $(wildcard $(p)),,$(info $(p) does not exist!) $(MAKE) sdl))
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJS_DIRECTORY):
	@mkdir -p $(OBJS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJS_DIRECTORY) was created$(RESET)"

$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

sdl:
	@echo "sad"
	cd SDL2; ./configure --prefix=$(DIRECTORY); make;
	$(MAKE) -sC $(DIRECTORY)/SDL2 install

$(SDL_LIBS):
	cd SDL2; ./configure --prefix=$(DIRECTORY); make;
	$(MAKE) -sC $(SDL_MAKE) install

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"
	@$(MAKE) -sC $(SDL_MAKE) clean
	@echo "$(SDL_MAKE): $(RED)object files were deleted$(RESET)"

dd:
	rm $(NAME)

fclean: clean
	@rm -rf $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
	@rm -f $(DIRECTORY)/bin/sdl2-config
	@rm -f $(DIRECTORY)/lib/libSDL2.la
	@rm -f $(DIRECTORY)/lib/libSDL2main.la
	@rm -f $(DIRECTORY)/lib/libSDL2_test.la
	@rm -f $(DIRECTORY)/share/aclocal/sdl2.m4
	@rm -f $(DIRECTORY)/lib/pkgconfig/sdl2.pc
	@rm -f $(DIRECTORY)/lib/cmake/SDL2/sdl2-config.cmake
	@rm -rf lib bin share
	@echo "$(SDL_MAKE): $(RED)was unistalled$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
#OBJS_DIRECTORY = objects/
#OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
#OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))
#SDL_LIBS = $(addprefix ./lib/, $(LIB_LIST))
#
#LIBFT = libft/libft.a
#LIBSDL_EXIST = 0
#err = no
#
#GREEN = \033[0;32m
#RED = \033[0;31m
#RESET = \033[0m
#
#.PHONY: all clean fclean re
#
#all: $(NAME)
#
#$(NAME): $(LIBFT) $(OBJS_DIRECTORY) $(OBJS)
#	$(foreach p,$(SDL_LIBS),$(if $(wildcard $(p)),,$(info $(p) does not exist!) $(MAKE) sdl))
#	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJS) -o $(NAME)
#	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
#	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"
#
#$(OBJS_DIRECTORY):
#	@mkdir -p $(OBJS_DIRECTORY)
#	@echo "$(NAME): $(GREEN)$(OBJS_DIRECTORY) was created$(RESET)"
#
#$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(HEADERS)
#	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
#	@echo "$(GREEN).$(RESET)\c"
#
#sdl:
#	@echo "sad"
#	cd SDL2; ./configure --prefix=$(DIRECTORY); make;
#	$(MAKE) -sC $(DIRECTORY)/SDL2 install
#
#$(SDL_LIBS):
#	cd SDL2; ./configure --prefix=$(DIRECTORY); make;
#	$(MAKE) -sC $(SDL_MAKE) install
#
#$(LIBFT):
#	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
#	@$(MAKE) -sC $(LIBFT_DIRECTORY)
#
#clean:
#	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
#	@rm -rf $(OBJS_DIRECTORY)
#	@echo "$(NAME): $(RED)$(OBJS_DIRECTORY) was deleted$(RESET)"
#	@echo "$(NAME): $(RED)object files were deleted$(RESET)"
#	@$(MAKE) -sC $(SDL_MAKE) clean
#	@echo "$(SDL_MAKE): $(RED)object files were deleted$(RESET)"
#
#dd:
#	rm $(NAME)
#
#fclean: clean
#	@rm -r $(LIBFT)
#	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
#	@rm -f $(NAME)
#	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
#	@rm -f $(DIRECTORY)/bin/sdl2-config
#	@rm -f $(DIRECTORY)/lib/libSDL2.la
#	@rm -f $(DIRECTORY)/lib/libSDL2main.la
#	@rm -f $(DIRECTORY)/lib/libSDL2_test.la
#	@rm -f $(DIRECTORY)/share/aclocal/sdl2.m4
#	@rm -f $(DIRECTORY)/lib/pkgconfig/sdl2.pc
#	@rm -f $(DIRECTORY)/lib/cmake/SDL2/sdl2-config.cmake
#	@rm -rf lib bin share
#	@echo "$(SDL_MAKE): $(RED)was unistalled$(RESET)"
#
#re:
#	@$(MAKE) fclean
#	@$(MAKE) all
