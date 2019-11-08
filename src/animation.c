/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:32:26 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/08 18:49:54 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_draw_animation(t_wolf3d *w)
{
	int x;
	int y;

	y = w->anim.place.y;
	while (y < w->anim.pframe.size.y + w->anim.place.y)
	{
		x = w->anim.place.x;
		while (x < w->anim.pframe.size.x + w->anim.place.x)
		{
			w->tex_col = &((Uint8 *)(w->weapon_texture->pixels))[(int)(3 *
			w->weapon_texture->w * (y - (int)(w->anim.place.y) +
			w->anim.pframe.cd.y) + (x - (int)(w->anim.place.x) +
			w->anim.pframe.cd.x) * 3)];
			w->color = *(Uint32 *)w->tex_col;
			w->color &= 0xFFFFFF;
			if (w->color != 0xFF00FF)
				w->sdl->pixels[x + (y * WIN_WIDTH)] = w->color;
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
		if (w->anim.frames && w->anim.frames % ONE_ANIM == 0)
			w->anim.pframe.cd.x += 512;
		else
		{
			if (w->anim.frames > FULL_ANIM)
			{
				w->anim.start_am = 0;
				w->anim.frames = 0;
				w->anim.pframe.cd.x = 0;
				w->t.flag = 1;
			}
		}
	}
}