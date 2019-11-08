#ifndef WOLF3D_H
# define WOLF3D_H
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define TEXTURES_NUMBER 23
# define THREADS 20
# define TEX_W 64
# define TEX_H 64
# define ONE_ANIM 20
# define FULL_ANIM ONE_ANIM * 4 - 4

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

typedef struct	s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct	s_rect
{
	t_coord		size;
	t_coord		cd;
}				t_rect;


typedef struct	s_anime
{
	int			start_am;
	int			frame;
	t_rect		pframe;
	t_coord		place;
	int			frames;
}				t_anime;

typedef struct	s_player
{
	t_coord		pos;
	t_coord		dir;
	t_coord		plane;
	t_coord		raydir;
	t_coord		side_dist;
	t_coord		delta_dist;
	double		old_dirX;
	double		old_planeX;
	double		cameraX;
	double		wall_dist;
	int			stepX;///?????
	int			stepY;
	int			side;
}				t_player;

typedef struct s_write
{
	t_list		*lst;
	char		**s;
	int			x;
	int			y;
	int			s_count;
}				t_write;


typedef struct  s_sdl
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
	
}				t_sdl;



typedef struct	s_map
{
	int			m_wid;
	int			m_hei;
	int			*map;
	int			x;
	int			y;
	int			s_count;
	//t_sprite	**sprite;
	int			*s_ord;
	double		*s_dst;
}				t_map;

typedef struct		s_const
{
	double	crs;
	double	srs;
	double	mcrs;
	double	msrs;
	double	camera_x_cnst;
	int		half_height;
}					t_const;

typedef struct		s_floor
{
	double	xwall;
	double	ywall;
	double	cur_dst;
	double	weight;
	double	cur_x;
	double	cur_y;
	int		text_x;
	int		text_y;
}					t_floor;

typedef struct		s_time
{
	Uint32			time;
	Uint32			old_time;
	Uint32			frame_time;
	Uint32			sound_old_time;
	Uint32			sound_time;
	Uint32			change_of_time;
	Uint32			play_time;
	Uint32			sound_sum_time;
	unsigned char	flag;
}					t_time;

typedef struct	s_wolf3d
{
	t_sdl			*sdl;
	t_map			map;
	t_time			t;
	t_const			c;
	t_player		pl;
	SDL_Surface		*weapon_texture;
	SDL_Surface		*map_texture;
	t_anime			anim;
	t_anime			view_map;
	t_floor			flr;
	int				temp;
	int				fd;
	int				x;
	int				y;
	int				hit;
	double			*z_buffer;
	double			ms;
	double			rs;
	unsigned char	arr[6];
	void			*tex_col;
	Uint32			color;

}				t_wolf3d;

typedef struct	s_thread_help
{
	t_player	pl;
	t_map		map;
	t_floor		flr;
	t_sdl		*sdl;
	void		*tex_col;
	double		*z_buffer;
	double		wall_hit;
	double		camera_x_cnst;
	Uint32		color;
	int			y;
	int			hit;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			texture_num;
	int			text_x;
	int			text_y;
	int			temp;
	int			half_height;
}				t_threads_help;

typedef struct	s_threads
{
	t_threads_help	w;
	int				t1;
	int				t2;
}				t_threads;


void				ft_clean_sdl(t_wolf3d *w);
int					ft_cleanmem(t_list **lst);
void				*ft_my_malloc(size_t s);
int					ft_error(char *code);
SDL_Surface			*ft_sdl_load_bmp(char *str);

void				read_file(int fd, t_map *map);
int					get_lines(int fd, t_list **lst);
void				get_map(t_map *m, int width, int height);
int					write_map(t_map *map, t_list *lst);

t_sdl				*sdl_init(t_sdl *sdl);
void				ft_init_wolf(t_wolf3d *w);
void				ft_we_need_more_init(t_wolf3d *w);
void				ft_init_multi_wolf(t_threads_help *w, t_wolf3d *head);
int					ft_init_anim(t_wolf3d *wolf);

void				ft_load_textures(t_wolf3d *w);
void				renderer(t_wolf3d *wolf);

void				ft_handle_events(t_wolf3d *w);
void				ft_use_events(t_wolf3d *w);
int					ft_step_back_check(t_wolf3d *w, unsigned char flag);
int					ft_step_forward_check(t_wolf3d *w, unsigned char flag);

void				ft_wall_hit(t_threads *a);
void				ft_wall_draw_start(t_threads *a);
void				ft_draw_walls(t_threads *a);

void				threading(t_wolf3d *w);

void				*begin_game(void *w);
int					ft_step_back_check(t_wolf3d *w, unsigned char flag);
int					ft_step_forward_check(t_wolf3d *w, unsigned char flag);
void				ft_ray_dir_calculations(t_threads *a);

void fpsthink();
void fpsinit();

void				ft_draw_animation(t_wolf3d *w);
void				ft_animation_play(t_wolf3d *w);

void				ft_draw_floor(t_threads *a);
void				ft_get_floor_coordinates(t_threads *a);

void				ft_init_sound(t_wolf3d *w);
void				ft_load_sound(t_wolf3d *w);
void				ft_play_shot(t_wolf3d *w);
void				ft_play_music(t_wolf3d *w);

int			ft_init_view_map(t_wolf3d *wolf);
void		ft_draw_map(t_wolf3d *w);

#endif
