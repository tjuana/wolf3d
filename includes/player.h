#ifndef PLAYER_H
# define PLAYER_H

# include "wolf3d.h"

typedef struct	s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct	s_stats
{
	int key[MAX_DOORS_NBR];
	int life;
	int	ammo;
	int money;
	int	jetpack;
}				t_stats;

typedef struct	s_player
{
	t_coord		pos;
	t_coord		dir;
	t_coord		plane;
	t_coord		raydir;
	t_coord		side_dist;
	t_coord		delta_dist;
	t_stats		st;
	double		old_dirX;
	double		old_planeX;
	double		cameraX;
	double		wall_dist;
	int			stepX; //?????
	int			stepY;
	int			side;
}				t_player;


#endif
