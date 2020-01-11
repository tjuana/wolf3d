//
// Created by Nymphadora Shelly on 08/01/2020.
//
#include "wolf3d.h"


int			ft_init_anim(t_wolf3d *wolf)
{
    wolf->anim.start_am = 0;
    wolf->anim.frame = 0;
    wolf->anim.pframe.size = (t_xy){512, 512};
    wolf->anim.pframe.crd = (t_xy){0, 0};
    wolf->anim.place = (t_xy){WIN_W / 2 - 512 / 2, WIN_H - 512};
    wolf->anim.frames = 0;
    return (0);
}

void		ft_draw_animation(t_wolf3d *w, SDL_Surface *surface)
{
    int x;
    int y;

    int *pix = (int*)surface->pixels;
    y = w->anim.place.y;
    while (y < w->anim.pframe.size.y + w->anim.place.y)
    {
        x = w->anim.place.x;
        while (x < w->anim.pframe.size.x + w->anim.place.x)
        {
            w->tex_col = &((int  *)(w->weapon_texture->pixels))[(int)(3 *
                                                                       w->weapon_texture->w * (y - (int)(w->anim.place.y) +
                                                                                               w->anim.pframe.crd.y) + (x - (int)(w->anim.place.x) +
                                                                                                                       w->anim.pframe.crd.x) * 3)];
            w->color = *(int *)w->tex_col;
            w->color &= 0xFFFFFF;
            if (w->color != 0xFF00FF)
                pix[x + (y * W)] = w->color;
            x++;
        }
        y++;
    }
}

void		ft_animation_play(t_wolf3d *w)
{
    if (w->anim.start_am == 1)
    {
        w->anim.frames++;
        if (w->anim.frames && w->anim.frames % 20 == 0)//ONE_ANIME WAS DELETED FROM OLD CODE
            w->anim.pframe.crd.x += 512;
        else
        {
            if (w->anim.frames > 76)//FROM ONE ANIME*4 - 4
            {
                w->anim.start_am = 0;
                w->anim.frames = 0;
                w->anim.pframe.crd.x = 0;
                //w->t.flag = 1;
            }
        }
    }
}

