/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:23:55 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/04 17:51:30 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "SDL.h"
# include "SDL_thread.h"
# include "SDL_mixer.h"
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <libft.h>
# include "constants.h"
# include "door.h"
# include "player.h"
# include "sprites.h"

typedef struct			s_sort_util
{
	int					i;
	int					j;
	int					count;
	char				swap;
}						t_sort_util;

typedef struct			s_rect
{
	t_coord				size;
	t_coord				cd;
}						t_rect;

typedef struct			s_anime
{
	int					start_am;
	int					frame;
	t_rect				pframe;
	t_coord				place;
	int					frames;
}						t_anime;

typedef struct			s_write
{
	t_list				*lst;
	char				**s;
	int					x;
	int					y;
	int					s_count;
}						t_write;

typedef struct			s_sdl
{
	int					running;
	SDL_Window			*win;
	SDL_Renderer		*renderer;
	Uint32				*pixels;
	SDL_Texture			*text;
	SDL_Surface			**surfaces;
	SDL_AudioSpec		*wav_spect;
	Uint32				*wav_len;
	Uint8				**wav_buff;
	SDL_AudioDeviceID	*audio_device;
	unsigned char		i;
}						t_sdl;

typedef struct			s_map
{
	int					m_wid;
	int					m_hei;
	int					*map;
	int					x;
	int					y;
	int					s_count;
	t_sprite			**sprite;
	int					*s_ord;
	double				*s_dst;
}						t_map;

typedef struct			s_floor
{
	double				xwall;
	double				ywall;
	double				cur_dst;
	double				weight;
	double				cur_x;
	double				cur_y;
	int					text_x;
	int					text_y;
}						t_floor;

typedef struct			s_time
{
	Uint32				time;
	Uint32				old_time;
	Uint32				frame_time;
	Uint32				sound_old_time;
	Uint32				sound_time;
	Uint32				change_of_time;
	Uint32				play_time;
	Uint32				sound_sum_time;
	unsigned char		flag;
}						t_time;

typedef struct			s_wolf3d
{
	t_sdl				*sdl;
	t_map				map;
	t_time				t;
	t_const				c;
	t_player			pl;
	SDL_Surface			*weapon_texture;
	SDL_Surface			*map_texture;
	t_anime				anim;
	t_anime				view_map;
	t_floor				flr;
	t_door				**doors;
	t_sprite_stats		spr;
	int					doors_nbr;
	int					temp;
	int					fd;
	int					x;
	int					y;
	int					hit;
	int					draw_start;
	int					draw_end;
	int					mouse_offset;
	double				*z_buffer;
	double				ms;
	double				rs;
	unsigned char		arr[66];
	Uint8				*tex_col;
	Uint32				color;
	int					stripe;
	int					i;

}						t_wolf3d;

typedef struct			s_thread_help
{
	t_player			pl;
	t_map				map;
	t_floor				flr;
	t_sdl				*sdl;
	void				*tex_col;
	double				*z_buffer;
	double				wall_hit;
	double				camera_x_cnst;
	Uint32				color;
	int					y;
	int					hit;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					texture_num;
	int					text_x;
	int					text_y;
	int					temp;
	int					half_height;
	int					mouse_offset;
}						t_threads_help;

typedef struct			s_threads
{
	t_threads_help		w;
	int					t1;
	int					t2;
}						t_threads;

typedef struct			s_fdf_wu
{
	double				x1;
	double				y1;
	double				x2;
	double				y2;
	double				p;
	double				dx;
	double				dy;
	double				gradient;
	double				xend;
	double				yend;
	double				xgap;
	double				xpxl1;
	double				ypxl1;
	double				xpxl2;
	double				ypxl2;
	double		    	intery;
	int					steep;
	int					steps;
	int					step;
	int					color1;
	int					color2;
	int					check_color_rev;
	double				temp_f;
}						t_fdf_wu;

typedef struct			s_fdf_get_color
{
	int					color1;
	int					color2;
	double				f1;
	int					r1;
	int					g1;
	int					b1;
	int					r2;
	int					g2;
	int					b2;
	int					r_rez;
	int					g_rez;
	int					b_rez;
}						t_fdf_get_color;

void					ft_door_create(t_wolf3d *w);
void					ft_door_open(t_wolf3d *w);

/*
 * ---------------------------alg_wu.c
 */
void					ft_fdf_init_wu(t_fdf_wu **wu, t_coord *dot_1, \
							t_coord *dot_2);
void					ft_fdf_swap_double(double *n1, double *n2);
void					ft_fdf_draw_line_swap(t_fdf_wu **wu);
void					ft_fdf_draw_line_param(t_wolf3d *data, t_fdf_wu **wu);
void					ft_fdf_wu(t_coord *dot_1, t_coord *dot_2, \
							t_wolf3d *data);

/*
 *---------------------------alg_wu_color.c
 */
void					ft_fdf_draw_line_first_pixels(t_wolf3d *data, \
							t_fdf_wu **wu);
void					ft_fdf_draw_line_last_pixels(t_wolf3d *data, \
							t_fdf_wu **wu);
void					ft_fdf_wu_cycle_x(t_wolf3d *data, t_fdf_wu *wu, \
							double x);
void					ft_fdf_wu_cycle_y(t_wolf3d *data, t_fdf_wu *wu, \
							double x);

int						ft_fdf_ipart(double x);
double					ft_fdf_round(double x);
double					ft_fdf_fpart(double x);
int						ft_fdf_get_color(int color1, int color2, double f1);

/*
 *---------------------------animation.c
 */
void					ft_draw_animation(t_wolf3d *w);
void					ft_animation_play(t_wolf3d *w);

/*
 * ---------------------------check_map.c
 * static int		ft_check_map_item(t_map *map, int i, int j, int empty_count)
 */
void					ft_check_map(t_map *map);

/*
 * ---------------------------draw_walls.c
 * static void			ft_wall_hit_switch(t_threads *a)
 */
void					ft_wall_hit(t_threads *a);
void					ft_wall_draw_start(t_threads *a);
void					ft_draw_walls(t_threads *a);

/*
 * ---------------------------events.c
 * static void		ft_keyup(t_wolf3d *w, SDL_Event e)
 * static void		ft_keydown(t_wolf3d *w, SDL_Event e)
 */
void					ft_handle_events(t_wolf3d *w);

/*
 * ---------------------------events_exp.c
 * static void		ft_use_events_exp(t_wolf3d *w)
 * static void		ft_right_rotation(t_wolf3d *w)
 * static void		ft_left_rotation(t_wolf3d *w)
 * static void		ft_left_right(t_wolf3d *w)
 */
void					ft_use_events(t_wolf3d *w);

/*
 * ---------------------------events_mouse.c
 */
void					ft_mouse_mv(SDL_Event *e, t_wolf3d *w);

/*
 * ---------------------------floor.c
 */
void					ft_draw_floor(t_threads *a);
void					ft_get_floor_coordinates(t_threads *a);

/*
 * ---------------------------help.c
 */
void					ft_clean_sdl(t_wolf3d *w);
int						ft_cleanmem(t_list **lst);
void					*ft_my_malloc(size_t s);
int						ft_error(char *code);
SDL_Surface				*ft_sdl_load_bmp(char *str);

/*
 * ---------------------------map.c
 * static void		ft_draw_map_text(t_wolf3d *w, int pos, int x, int y)
 * static int	pos_calc(t_wolf3d *w, int x, int y)
 * static int	ft_check_map_pos(t_wolf3d *w, int pos, int x, int y)
 */
int						ft_init_view_map(t_wolf3d *wolf);
void					ft_draw_map(t_wolf3d *w);

/*
 * ---------------------------map_arrow.c
 * static void		ft_draw_compass_arrow(t_wolf3d *w)
 */
void			ft_draw_compass(t_wolf3d *w);//maybe we dont need this, CHECK!!!

/*
 * ---------------------------move.c
 * static void		ft_draw_compass_arrow(t_wolf3d *w)
 */
int						ft_step_back_check(t_wolf3d *w, unsigned char flag);
int						ft_step_forward_check(t_wolf3d *w, unsigned char flag);
int						ft_step_left_check(t_wolf3d *w, unsigned char flag);
int						ft_step_right_check(t_wolf3d *w, unsigned char flag);

/*
 * ---------------------------ray_casting.c
 * static void			ft_ray_dir_calculations_helper(t_threads *a)
 */
void					ft_ray_dir_calculations(t_threads *a);

/*
 * ---------------------------read_map.c
 */
void					read_file(int fd, t_map *map);
int						get_lines(int fd, t_list **lst);
void					get_map(t_map *m, int width, int height);
int						write_map(t_map *map, t_list *lst);
void					write_sprites(t_map *m);

/*
 * ---------------------------sdl.c
 */
t_sdl					*sdl_init(t_sdl *sdl);
void					ft_init_wolf(t_wolf3d *w);
void					ft_we_need_more_init(t_wolf3d *w);
void					ft_init_multi_wolf(t_threads_help *w, t_wolf3d *head);
int						ft_init_anim(t_wolf3d *wolf);

/*
 * ---------------------------sdl_error.c
 */
void					ft_sdl_error(t_wolf3d *w);

/*
 * ---------------------------sdl_render.c
 */
void					renderer(t_wolf3d *wolf);

/*
 * ---------------------------sound.c
 */
void					ft_init_sound(t_wolf3d *w);
void					ft_load_sound(t_wolf3d *w);
void					ft_play_shot(t_wolf3d *w);
void					ft_play_music(t_wolf3d *w);

/*
 * ---------------------------sprites.c
 */
void	                ft_draw_sprites(t_wolf3d *w);
void	                ft_calculate_sprites(t_wolf3d *w);
void	                ft_show_sprites(t_wolf3d *w);
void	                ft_transform_sprites(t_wolf3d *w);

/*
 * ---------------------------sprites_help.c
 * static void ft_swap_double(double *a, double *b)
 */
void					ft_sort(t_wolf3d *w);

/*
 * ---------------------------textures.c
 */
void					ft_load_textures(t_wolf3d *w);

/*
 * ---------------------------threads.c
 */
void					threading(t_wolf3d *w);
void					*begin_game(void *w);
#endif
