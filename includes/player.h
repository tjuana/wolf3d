#ifndef PLAYER_H
#define PLAYER_H
# include "wolf3d.h"

typedef struct	s_player
{
	t_xy		t1;
	t_xy		t2;
	t_xy		scale_1;
	t_xy		scale_2;
    t_xyz		where;      // Current position
    t_xyz		velocity;   // Current motion vector
    float		angle;
    float		anglesin;
    float		anglecos;
    float		yaw;   // Looking towards (and sin() and cos() thereof)
    unsigned	sector;// Which sector the player is currently in
    t_sector	*sectors;
	int			neighbor;
	t_ceil		ceil;
	t_floor		floor;
	float		nearz;
	float		farz;
	float		nearside;
	float		farside;
	int			x1;
	int			x2;
}				t_player;

#endif
