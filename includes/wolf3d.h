#ifndef WOLF3D_H
# define WOLF3D_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_thread.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_image.h"
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <libft.h>
# include "constants.h"
# include "help.h"
# include "animations.h"
# include "engine.h"
# include "events.h"
# include "player.h"
//# include <dirent.h>

static unsigned NumSectors = 0;

typedef struct	s_w
{
    t_anime		anim;
    int			*tex_col;
    SDL_Surface	*weapon_texture;
    int			color;
}				t_wolf3d;


float		min(float a, float b);
float		max(float a, float b);
float		clamp(float a, float mi, float ma);
float		vxs(float x0, float y0, float x1, float y1);
int			Overlap(float a0, float a1, float b0, float b1);
int			IntersectBox(float x0, float y0, float x1, float y1,float x2, float y2, float x3, float y3);
float		PointSide(float px, float py, float x0, float y0,float x1, float y1);
t_xy		Intersect(float x1, float y1, float x2, float y2,float x3, float y3, float x4, float y4);
void		UnloadData();
void		MovePlayer(float dx, float dy, t_player *player);
float		Yaw(float y, float z, t_player *player);

/*			engine.c			*/

/*			engine_exp.c			*/
int			engine_cross(t_player *pl, int sec_n, unsigned s);
void		engine_scale(t_player *pl, float tz1, float tz2);

/*			functions_main.c			*/

int			sub_events(t_subevents *se, t_player *player);
int			events(t_subevents *se, t_player *player);
void		mouse_movement(t_mouse *ms, t_player *player);
void		vectors_vel_dir(t_player *player, t_subevents *se, t_others *ot);
void		sectors_ops(t_sector_ops *op, t_player *player, t_others *ot, t_subevents *se);
void		jumps(t_subevents *se, t_player *player, t_sector_ops *op, t_others *ot);

/*			animations.c			*/

int			ft_init_anim(t_wolf3d *wolf);
void		ft_draw_animation(t_wolf3d *w, SDL_Surface *surface);
void		ft_animation_play(t_wolf3d *w);


#endif
