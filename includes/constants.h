#ifndef CONSTANTS_H
# define CONSTANTS_H
# define WIN_HEIGHT 800
# define WIN_WIDTH 1420
# define TEXTURES_NUMBER 23
# define THREADS 10
# define TEX_W 64
# define TEX_H 64
# define ONE_ANIM 20
# define FULL_ANIM ONE_ANIM * 4 - 4
# define KEYS_NBR 66
# define MAX_DOORS_NBR 20
# define MAX_AMMO 280
# define MAX_LIFE 200
# define MOB_SPD 0.000005

# define C_R 0x00FF0000
# define C_G 0x0000FF00
# define C_B 0x000000FF

typedef struct			s_const
{
	double				crs;
	double				srs;
	double				mcrs;
	double				msrs;
	double				camera_x_cnst;
	int					half_height;
}						t_const;

#endif
