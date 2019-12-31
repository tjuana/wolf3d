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

typedef struct			s_coord
{
	double				x;			// Координата точки по x
	double				y;			// Координата точки по y
}						t_coord;

// new struct for line
typedef struct			s_line
{
	t_coord				p1;			// Координаты первой точки
	t_coord				p2;			// Координаты второй точки
	double				height;		// Высота стены
	double				floor;		// Высота ~ от z = 0
	int					txtr;		// Номер текстуры
}						t_line;

// new struct for sector
typedef struct			s_sector
{
	t_coord				**vertex;		// Указатель на массив вершин
	int					vertex_count;
	double				height;		// Высота стены
	double				floor;		// Высота ~ от z = 0
	int					txtr;		// Номер текстуры сектора (?)
}						t_sector;

typedef struct			s_sort_util	// Структура для спрайтов (?)
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

typedef struct			s_player
{
	t_coord				pos;			// Позиция игрока
	t_coord				dir;			// Вектор направления игрока
	t_coord				plane;			// Зависимость от ширины и высоты экрана
	t_coord				raydir;			// Направление луча
	t_coord				side_dist;		// Длина смещения при поиске стены (уст.)
	t_coord				delta_dist;		// Шаг смещения при поиске стены (уст.)
	double				old_dirX;		// temp-переменная для хранения dir.x
	double				old_planeX;		// temp-переменная для хранения plane.x
	double				cameraX;		// Смещение луча от центра камеры (-1.0 ... 1.0)
	double				cameraH;		// Высота камеры (-1.0 ... 1.0)
	double				camera_tilt;	// Смещение камеры
	double				wall_dist;		// Дистанция до стены с коррекцией fish eyes
	int					stepX;			// flag: направление луча по x (уст.)
	int					stepY;			// flag: направление луча по y (уст.)
	int					side;			// flag: сторона (например, подкрашивает стены)
}						t_player;

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
	SDL_Surface			**textures;
	SDL_AudioSpec		*wav_spect;
	Uint32				*wav_len;
	Uint8				**wav_buff;
	SDL_AudioDeviceID	*audio_device;
	unsigned char		i;
	
}						t_sdl;

typedef struct			s_sprite
{
	double				x;
	double				y;
	double				distance;
	int					texture;
}						t_sprite;

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

typedef struct			s_const
{
	double				crs;
	double				srs;
	double				mcrs;
	double				msrs;
	double				camera_x_cnst;
	int					half_height;
}						t_const;

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
	// add list with lines
	t_list				*line;
	// add list with sector
	t_list				*sector;
	// spec param
	double				fov;
	double				l_p;

	t_sdl				*sdl; //structe for handle sdl  stuff
	t_map				map;
	t_time				t;
	t_const				c;
	t_player			pl;
	SDL_Surface			*weapon_texture;
	SDL_Surface			*map_texture;
	t_anime				anim;
	t_anime				view_map;
	t_floor				flr;
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
	// add list with lines
	t_list				*line;
	// spec param
	double				l;
	double				fov;
	double				l_p;
	t_coord				fc_dir;
	t_coord				ln_dir;
	double				ln_l;

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

void					read_file(int fd, t_map *map);
int						get_lines(int fd, t_list **lst);
void					get_map(t_map *m, int width, int height);
int						write_map(t_map *map, t_list *lst);

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

void					ft_wall_hit(t_threads *a);
void					ft_wall_draw_start(t_threads *a);
void					ft_draw_walls(t_threads *a);

void					threading(t_wolf3d *w);

void					*begin_game(void *w);
int						ft_step_back_check(t_wolf3d *w, unsigned char flag);
int						ft_step_forward_check(t_wolf3d *w, unsigned char flag);
void					ft_ray_dir_calculations(t_threads *a);

// fps
void					fpsthink(void);
void					fpsinit(void);

void					ft_draw_animation(t_wolf3d *w);
void					ft_animation_play(t_wolf3d *w);

void					ft_draw_floor(t_threads *a);
void					ft_get_floor_coordinates(t_threads *a);

void					ft_init_sound(t_wolf3d *w);
void					ft_load_sound(t_wolf3d *w);
void					ft_play_shot(t_wolf3d *w);
void					ft_play_music(t_wolf3d *w);

int						ft_init_view_map(t_wolf3d *wolf);
void					ft_draw_map(t_wolf3d *w);

void					ft_sort(t_wolf3d *w);
void					write_sprites(t_map *m);

void					ft_fdf_init_wu(t_fdf_wu **wu, t_coord *dot_1, \
							t_coord *dot_2);
void					ft_fdf_swap_double(double *n1, double *n2);
void					ft_fdf_draw_line_swap(t_fdf_wu **wu);
void					ft_fdf_draw_line_param(t_wolf3d *data, t_fdf_wu **wu);
void					ft_fdf_wu(t_coord *dot_1, t_coord *dot_2, \
							t_wolf3d *data);

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

void					ft_set_line(t_wolf3d *w, t_line *line,
							t_line temp_line, t_list *lst);

void					ft_read_file_nmp(int fd, t_wolf3d *w);
void					ft_draw_map_new_line(t_wolf3d *w);
void					ft_draw_map_new_sector(t_wolf3d *w);

#endif
