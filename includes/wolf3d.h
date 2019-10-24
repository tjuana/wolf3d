#ifndef WOLF3D_H
# define WOLF3D_H
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define TEXTURES_NUMBER 23

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


typedef struct  s_sdl
{
    int					running;
	SDL_Window			*win;
	SDL_Renderer		*renderer;
	Uint32				*text_buf;
	SDL_Texture			*text;
	SDL_Surface			**textures;
	SDL_AudioSpec		*wav_spect;
	Uint32				*wav_len;
	Uint8				**wav_buff;
	SDL_AudioDeviceID	*audio_device;
	unsigned char		i;
}				t_sdl;

typedef struct	s_coord
{
	double		x;
	double		y;
}				t_coord;


typedef struct s_write
{
	t_list		*lst;
	char		**s;
	int			x;
	int			y;
	int			s_count;
}				t_write;


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

typedef struct		s_const
{
	double	crs;
	double	srs;
	double	mcrs;
	double	msrs;
	double	camera_x_cnst;
	int		half_height;
}					t_const;

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


typedef struct	s_wolf3d
{
	t_sdl			*sdl;
	t_map			map;
	t_time			t;
	t_const			c;
	t_player		pl;
	SDL_Surface		*weapon_texture;
	int				fd;
	int				x;
	int				y;
	int				hit;
	double			*z_buffer;
	double			ms;
	double			rs;
	unsigned char	arr[5];	
}				t_wolf3d;


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
void				ft_load_textures(t_wolf3d *w);
void				renderer(t_wolf3d *wolf);

#endif