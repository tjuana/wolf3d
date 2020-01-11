#ifndef EVENTS_H
#define EVENTS_H
# include "wolf3d.h"

typedef struct	s_subevents
{
    SDL_Event	ev;
    int			wsad[4];
    int			ground;
    int			falling;
    int			ducking;
    int			quit;
}				t_subevents;

typedef struct	s_mouse
{
    int		x;
    int		y;
    float	yaw;
}				t_mouse;

#endif
