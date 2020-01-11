#ifndef ANIMATIONS_H
#define ANIMATIONS_H
# include "wolf3d.h"

typedef struct			s_anime
{
	int					start_am;
	int					frame;
	t_rect				pframe;
	t_rect				place;
	int					frames;
}						t_anime;

#endif
