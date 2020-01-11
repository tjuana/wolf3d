#ifndef ENGINE_H
#define ENGINE_H
# include "wolf3d.h"

typedef struct	s_sector//have to be static
{
    float		floor;
	float		ceil;
    t_xy		*vertex; // Each vertex has an x and y coordinate
    signed char	*neighbors;           // Each edge may have a corresponding neighboring sector
    unsigned	npoints;                 // How many vertexes there are
}				t_sector;//*sectors = NULL;

typedef struct s_sector_ops
{
    float			px;
    float			dx;
    float			py;
    float			dy;
    const t_sector	*sect;
    const t_xy		*vert;
    float			eyeheight;
    float			hole_low;
    float			hole_high;
    float			xd;
    float			yd;
}					t_sector_ops;

typedef struct	s_others
{
    float	move_vec[2];
    int		moving;
}			t_others;

typedef struct	s_ceil //y - height of ceil, n - neighbor, a - left, b - right
{
	float	yceil;//ceiling heights, relative to where the player's view is
	float	nyceil;//boundary between two neighbor sectors
	
	int		y1a;//ceil projection
	int		y2a;//ceil projection
	int		ny1a;//projection neighbor
	int		ny2a;//projection neighbor

	int		cya;//Y coordinates for our ceil in this X coordinate (top)
	int		cyb;//Y coordinates for our ceil in this X coordinate (bottom)
	int		cnya;//Y coordinates for neighbor ceil in this X coordinate
	int		cnyb;//Y coordinates for neighbor ceil in this X coordinate
}				t_ceil;

typedef struct	s_floor//y - height of floor, n - neighbor, a - left, b - right
{
	float	yfloor;//floor heights, relative to where the player's view is
	float	nyfloor;//boundary between two neighbor sectors

	int		y1b;//floor projection 
	int		y2b;//floor projection
	int		ny1b;//floor projection neighbor
	int		ny2b;//floor projection neighbor
	
	int		ya;//Y coordinates for our floor in this X coordinate
	int		yb;//Y coordinates for our floor in this X coordinate
	int		nya;//Y coordinates for neighbor floor in this X coordinate
	int		nyb;//Y coordinates for neighbor floor in this X coordinate
}				t_floor;

#endif