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
	/*SDL_Surface	*life_surf;
	SDL_Surface	*ammo_surf;
	SDL_Surface	*money_surf;
	SDL_Surface	*jet_surf;*/
	
	int			key[MAX_DOORS_NBR];
	int			door_nbr;
	int			life;
	int			ammo;
	int			money;
	int			jetpack;
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
	double		old_dirx;
	double		old_planex;
	double		camerax;
	double		wall_dist;
	int			stepx; //?????
	int			stepy;
	int			side;
}				t_player;


#endif
