#ifndef WOLF3D_H
# define WOLF3D_H
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define TEXTURES_NUMBER 23
# define THREADS 1
# define TEX_W 64
# define TEX_H 64
# define ONE_ANIM 20
# define FULL_ANIM ONE_ANIM * 4 - 4
# define T_CAM_HR_ANGLE 0.02 // transform angle for camera
# define T_CAM_Z_ANGLE 0.01 // transform angle for camera

# define DEG_30 0.52360

# define C_R 0x00FF0000
# define C_G 0x0000FF00
# define C_B 0x000000FF

# include "SDL2/SDL.h"
# include "SDL2/SDL_thread.h"
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <libft.h>
// matrix library
//# include "matrix/constants.h"
// # include "matrix/door.h"
// # include "matrix/player.h"
// # include "matrix/sprites.h"
//# include "matrix/sdl.h"
//# include "matrix/fdf.h"
# include "algebra.h" // math library for matrix transform

// new struct for sector
typedef struct			s_sector
{
	int					id;
	t_vector3			**vertex;		// Указатель на массив вершин
	int					vertex_count;	// Кол-во вершин в секторе
	int					**neighbors;	// Номера соседних секторов
	double				height;			// Высота стены
	double				floor;			// Высота ~ от z = 0
	int					txtr_floor;		// Номер текстуры сектора (?)
	int					txtr_walls;		// Номер текстуры сектора (?)
	int					txtr_ceil;		// Номер текстуры сектора (?)
	int					color;			// Цвет сектора (temp)
}						t_sector;

typedef struct			s_sort_util	// Структура для спрайтов (?)
{
	int					i;
	int					j;
	int					count;
	char				swap;
}						t_sort_util;

typedef struct			s_rect		// (?)
{
	t_vector3			size;
	t_vector3			cd;
}						t_rect;


typedef struct			s_anime
{
	int					start_am;
	int					frame;
	t_rect				pframe;
	t_vector3			place;
	int					frames;
}						t_anime;

typedef struct			s_player
{
	t_vector3			camera_vector;	// Основной вектор камеры
	t_vector3			pos;			// Позиция игрока
	double				cameraX;		// temp: Смещение луча от центра камеры (-1.0 ... 1.0)
	double				cameraH;		// Высота камеры (-1.0 ... 1.0)
	double				wall_dist;		// temp: Дистанция до стены с коррекцией fish eyes
	int					side;			// flag: сторона (например, подкрашивает стены)
}						t_player;

typedef struct			s_write			// Для чтения карты
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
	SDL_Surface			**textures;
	SDL_AudioSpec		*wav_spect;
	Uint32				*wav_len;
	Uint8				**wav_buff;
	SDL_AudioDeviceID	*audio_device;
	unsigned char		i;
	
}						t_sdl;

/*
	Old sprite struct
*/
typedef struct			s_sprite
{
	double				x;
	double				y;
	double				distance;
	int					texture;
}						t_sprite;

/*
	New sprite struct (example)
*/
typedef struct			s_sprite_new
{
	int					type;			// 0: static, 1: dynamic (enemy?)
	t_vector3			pos;			// xyz-w coord.
	double				distance;
	int					texture;
}						t_sprite_new;

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

/*
	Some point about crs, src, mcrs and msrs constants.
	These constants are helpers for rotations. If we will use them,
	our calculations will be simpler. But we don't have
	matrix functions for constant parameters.
*/
typedef struct			s_const			// structure for constants
{
	double				crs;			// [now not use]
	double				srs;			// [now not use]
	double				mcrs;			// [now not use]
	double				msrs;			// [now not use]
	double				camera_x_cnst;	// useful constant for camera offset
	int					half_height;	// [not use]
}						t_const;

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
	// add list with sector
	t_list				*sector;
	// add temp list for map
	t_list				*map_sector;
	// add temp list for map (top vertex)
	t_list				*map_sector_top;
	// spec param
	double				fov;
	double				l_p;

	t_list				*sprites;

	t_sdl				*sdl; //structe for handle sdl  stuff
	t_map				map;
	t_time				t;
	t_const				c;
	t_player			pl;
	SDL_Surface			*weapon_texture;
	SDL_Surface			*map_texture;
	t_anime				anim;
	t_anime				view_map;
	int					temp;
	int					fd;
	int					x;
	int					y;
	int					hit;
	double				*z_buffer;
	double				ms;
	double				rs;
	unsigned char		arr[10];
	Uint8				*tex_col;
	Uint32				color;

	int					type;

}						t_wolf3d;

typedef struct			s_thread_help
{
	// add list with sector
	t_list				*sector;
	// spec param
	double				l;
	double				fov;
	double				l_p;
	t_vector3			fc_dir;
	t_vector3			ln_dir;
	double				ln_l;

	t_player			pl;
	t_map				map;
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
	int					wall_color; // temp
	int					text_x;
	int					text_y;
	int					temp;
	int					half_height;
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
	double				intery;
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
	int					color1;	// Первый цвет
	int					color2;	// Второй цвет
	double				f1;		// Полупрозрачность первого цвета
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


void					ft_clean_sdl(t_wolf3d *w);
int						ft_cleanmem(t_list **lst);
void					*ft_my_malloc(size_t s);
int						ft_error(char *code);
SDL_Surface				*ft_sdl_load_bmp(char *str);

t_sdl					*sdl_init(t_sdl *sdl);
void					ft_init_wolf(t_wolf3d *w);
void					ft_we_need_more_init(t_wolf3d *w);
void					ft_init_multi_wolf(t_threads_help *w, t_wolf3d *head);
int						ft_init_anim(t_wolf3d *wolf);

void					ft_load_textures(t_wolf3d *w);
void					renderer(t_wolf3d *wolf);

void					ft_handle_events(t_wolf3d *w);
void					ft_use_events(t_wolf3d *w);
int						ft_step_back_check(t_wolf3d *w, unsigned char flag);
int						ft_step_forward_check(t_wolf3d *w, unsigned char flag);

void					threading(t_wolf3d *w);

void					*begin_game(void *w);
int						ft_step_back_check(t_wolf3d *w, unsigned char flag);
int						ft_step_forward_check(t_wolf3d *w, unsigned char flag);

// fps
void					fpsthink(void);
void					fpsinit(void);

void					ft_draw_animation(t_wolf3d *w);
void					ft_animation_play(t_wolf3d *w);

void					ft_init_sound(t_wolf3d *w);
void					ft_load_sound(t_wolf3d *w);
void					ft_play_shot(t_wolf3d *w);
void					ft_play_music(t_wolf3d *w);

int						ft_init_view_map(t_wolf3d *wolf);
void					ft_draw_map(t_wolf3d *w);

void					ft_sort(t_wolf3d *w);
void					write_sprites(t_map *m);

void					ft_fdf_init_wu(t_fdf_wu **wu, t_vector3 *dot_1, \
							t_vector3 *dot_2);
void					ft_fdf_swap_double(double *n1, double *n2);
void					ft_fdf_draw_line_swap(t_fdf_wu **wu);
void					ft_fdf_draw_line_param(t_wolf3d *data, t_fdf_wu **wu);
void					ft_fdf_wu(t_vector3 *dot_1, t_vector3 *dot_2, \
							t_wolf3d *data);

void					ft_fdf_wu_color(t_vector3 *dot_1, t_vector3 *dot_2, \
							t_wolf3d *data, int color);
void					ft_fdf_init_wu_color(t_fdf_wu **wu, t_vector3 *dot_1, \
							t_vector3 *dot_2, int color);

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

void					ft_draw_compass(t_wolf3d *w);
void					ft_draw_compass_static(t_wolf3d *w);

void					ft_read_file_nmp(int fd, t_wolf3d *w);
void					ft_draw_map_new_line(t_wolf3d *w);
void					ft_draw_map_new_sector(t_wolf3d *w);
void					ft_draw_map_new_sector_iso(t_wolf3d *w);

void					ft_debug_matrix(t_matrix_4x4 matrix);

int						ft_check_point_in_line_segment(t_vector3 p, t_vector3 p1, t_vector3 p2);
int						ft_check_div(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4);
t_vector3				ft_find_intersect(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4);
int						ft_get_player_sector(t_wolf3d *w);

int						ft_check_point(t_vector3 p, t_vector3 p1, t_vector3 p2, t_vector3 p1_pl, t_vector3 p2_pl);

void					ft_sector_list_cast(t_threads *a);
int						ft_check_point_fov(t_vector3 p, t_vector3 p1, t_vector3 p2, t_vector3 p1_pl, t_vector3 p2_pl);

void					ft_print_sectors(t_list *ptr_list);

/*
**	Parser functions
*/
int				ft_parser_get_vertexes_count(char *str);
t_vector3		ft_parser_nnmp_get_vertex(char **ptr, char *ptr_finish);
t_vector3		*ft_parser_nnmp_vertex(char **ptr);

void			ft_parser_nnmp_player(t_wolf3d *w, char **line);
void			ft_parser_nnmp_sprite(t_wolf3d *w, char **line);
void			ft_parser_nnmp_enemy(t_wolf3d *w, char **line);
void			ft_parser_nnmp(int fd, t_wolf3d *w);

void			ft_parser_nnmp_sector_neighborhood(t_wolf3d *w, char **line, \
					t_sector *sector);
void			ft_parser_nnmp_sector_vertexes(t_wolf3d *w, char **line, \
					t_sector *sector);
void			ft_parser_nnmp_sector_param(t_wolf3d *w, char **line, \
					t_sector *sector);
void			ft_parser_nnmp_sector(t_wolf3d *w, char **line);

char			*ft_parser_search_param(char *line, char *needly);
int				ft_parser_get_param(char *line, char *needly);

#endif
