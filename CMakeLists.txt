cmake_minimum_required(VERSION 3.15)
project(doom_nukem C)

set(CMAKE_C_STANDARD 99)

add_executable(doom_nukem src/alg_wu_color.c src/alg_wu_draw.c  src/alg_wu.c  src/animation.c src/draw_walls.c
        src/floor.c src/help.c src/read_map.c src/events.c src/events_exp.c src/events_mouse.c src/main.c
        src/move.c src/map.c src/map_arrow.c src/ray_casting.c src/sdl.c src/sdl_error.c src/sdl_render.c
        src/sound.c src/textures.c src/threads.c src/check_map.c src/sprites.c src/sprites_help.c)

include_directories (include/SDL2/ includes/ libft/)

find_library(SDL2 SDL2 lib)
find_library(FT ft libft)

target_link_libraries(doom_nukem LINK_PUBLIC ${SDL2})
target_link_libraries(doom_nukem LINK_PUBLIC ${FT})