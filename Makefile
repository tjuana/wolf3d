# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 11:40:58 by tjuana            #+#    #+#              #
#    Updated: 2020/01/10 19:31:23 by dorange-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
EDITOR_NAME = map_editor

FLAGS = -g -O3 
CC = gcc
LIBRARIES = \
	-lft -L$(LIBFT_DIRECTORY) -F SDL2/Frameworks \
	-lSDL2 -L$(SDL_DIRECTORY) -lSDL2main -L$(SDL_DIRECTORY) \
	-lSDL2-2.0.0 -L$(SDL_DIRECTORY)
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(SDL_HEADERS)

LIBFT = $(addprefix $(LIBFT_DIRECTORY),libft.a)
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = ./libft/includes
SDL_HEADERS = include/

HEADERS_DIRECTORY = ./includes/
HEADERS_LIST = wolf3d.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

DIRECTORY =  $(shell pwd)

SDL_DIRECTORY = $(DIRECTORY)/lib
SDL_MAKE = $(DIRECTORY)/SDL2

LIB_LIST =	libSDL2.a\
			libSDL2.la\
			libSDL2_test.la\
			libSDL2main.la\
			libSDL2-2.0.0.dylib\
			libSDL2.dylib\
			libSDL2_test.a\
			libSDL2main.a

PARSER_DIRECTORY = ./src/parser/
PARSER_LIST = parser_func.c parser_nnmp_sector.c parser_nnmp.c parser_vertex.c

PARSER_OBJS_DIRECTORY = ./obj_parser/
PARSER_OBJS_LIST = $(patsubst %.c, %.o, $(PARSER_LIST))
PARSER_OBJS = $(addprefix $(PARSER_OBJS_DIRECTORY), $(PARSER_OBJS_LIST))

SRCS_DIRECTORY = ./src/
SRCS_LIST = \
			help.c\
			read_map.c\
			sdl.c\
			textures.c\
			events.c\
			threads.c\
			sdl_render.c\
			move.c\
			fpc.c\
			animation.c\
			sound.c	\
			map.c \
			alg_wu_color.c \
			alg_wu_draw.c \
			alg_wu.c \
			map_arrow.c \
			vectors_1.c \
			vectors_2.c \
			matrix.c \
			debug.c \
			sector.c

OBJS_DIRECTORY = ./objects/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))



MAIN_SRCS_DIRECTORY = ./src/
MAIN_SRCS_LIST = main.c

MAIN_OBJS_DIRECTORY = ./obj_main/
MAIN_OBJS_LIST = $(patsubst %.c, %.o, $(MAIN_SRCS_LIST))
MAIN_OBJS = $(addprefix $(MAIN_OBJS_DIRECTORY), $(MAIN_OBJS_LIST))



EDITOR_SRCS_DIRECTORY = ./src/editor/
EDITOR_SRCS_LIST = editor.c render.c map.c events.c mouse.c draw.c

EDITOR_OBJS_DIRECTORY = ./obj_editor/
EDITOR_OBJS_LIST = $(patsubst %.c, %.o, $(EDITOR_SRCS_LIST))
EDITOR_OBJS = $(addprefix $(EDITOR_OBJS_DIRECTORY), $(EDITOR_OBJS_LIST))



SDL_LIBS = $(addprefix $(DIRECTORY)/lib/, $(LIB_LIST))

LIBFT = libft/libft.a
LIBSDL_EXIST = 0
err = no

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME) $(EDITOR_NAME)

$(NAME): $(LIBFT) $(OBJS_DIRECTORY) $(PARSER_OBJS_DIRECTORY) $(MAIN_OBJS_DIRECTORY) $(OBJS) $(PARSER_OBJS) $(MAIN_OBJS)
	$(foreach p,$(SDL_LIBS),$(if $(wildcard $(p)),,$(info $(p) does not exist!) $(MAKE) sdl))
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJS) $(MAIN_OBJS) $(PARSER_OBJS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJS_DIRECTORY):
	@mkdir -p $(OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@echo "$(NAME): $(GREEN)$(OBJS_DIRECTORY) was created$(RESET)"

$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(PARSER_OBJS_DIRECTORY):
	@mkdir -p $(PARSER_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@echo "$(NAME): $(GREEN)$(PARSER_OBJS_DIRECTORY) was created$(RESET)"

$(PARSER_OBJS_DIRECTORY)%.o : $(PARSER_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(MAIN_OBJS_DIRECTORY):
	@mkdir -p $(MAIN_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@echo "$(NAME): $(GREEN)$(MAIN_OBJS_DIRECTORY) was created$(RESET)"

$(MAIN_OBJS_DIRECTORY)%.o : $(MAIN_SRCS_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"



$(EDITOR_NAME): $(LIBFT) $(EDITOR_OBJS_DIRECTORY) $(EDITOR_OBJS) $(OBJS)
	$(foreach p,$(SDL_LIBS),$(if $(wildcard $(p)),,$(info $(p) does not exist!) $(MAKE) sdl))
	@echo $(EDITOR_OBJS) $(OBJS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(EDITOR_OBJS) $(OBJS) $(PARSER_OBJS) -o $(EDITOR_NAME)
	@echo "\n$(EDITOR_NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(EDITOR_NAME): $(GREEN)$(EDITOR_NAME) was created$(RESET)"

$(EDITOR_OBJS_DIRECTORY):
	@mkdir -p $(EDITOR_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@echo "$(EDITOR_NAME): $(GREEN)$(EDITOR_OBJS_DIRECTORY) was created$(RESET)"

$(EDITOR_OBJS_DIRECTORY)%.o : $(EDITOR_SRCS_DIRECTORY)%.c $(HEADERS)
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
	@rm -rf $(PARSER_OBJS_DIRECTORY)
	@echo "$(NAME): $(RED)$(PARSER_OBJS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"
	@$(MAKE) -sC $(SDL_MAKE) clean
	@echo "$(SDL_MAKE): $(RED)object files were deleted$(RESET)"

dd:
	rm $(NAME)

fclean: clean
	@rm -r $(LIBFT)
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
