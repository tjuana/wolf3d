/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:18:24 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/11 20:38:41 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** 4 different wall directions possible
*/

void	ft_get_floor_coordinates(t_threads *a)
{
	if (a->w.pl.side == 0 && a->w.pl.raydir.x > 0)
	{
		a->w.flr.xwall = a->w.map.x;
		a->w.flr.ywall = a->w.map.y + a->w.wall_hit;
	}
	else if (a->w.pl.side == 0 && a->w.pl.raydir.x < 0)
	{
		a->w.flr.xwall = a->w.map.x + 1.0;
		a->w.flr.ywall = a->w.map.y + a->w.wall_hit;
	}
	else if (a->w.pl.side == 1 && a->w.pl.raydir.y > 0)
	{
		a->w.flr.xwall = a->w.map.x + a->w.wall_hit;
		a->w.flr.ywall = a->w.map.y;
	}
	else
	{
		a->w.flr.xwall = a->w.map.x + a->w.wall_hit;
		a->w.flr.ywall = a->w.map.y + 1.0;
	}
	if (a->w.draw_end < 0)
		a->w.draw_end = WIN_HEIGHT;
}

/*
** draw the floor from draw_end to the bottom of the screen
*/

void	ft_draw_floor(t_threads *a)
{
	a->w.y = a->w.draw_end + 1;
	while (a->w.y < WIN_HEIGHT)
	{
		a->w.flr.cur_dst = WIN_HEIGHT / (2.0 * a->w.y - WIN_HEIGHT);
		a->w.flr.weight = a->w.flr.cur_dst / a->w.pl.wall_dist;
		a->w.flr.cur_x = a->w.flr.weight * a->w.flr.xwall +
		(1.0 - a->w.flr.weight) * a->w.pl.pos.x;
		a->w.flr.cur_y = a->w.flr.weight * a->w.flr.ywall +
		(1.0 - a->w.flr.weight) * a->w.pl.pos.y;
		a->w.flr.text_x = (int)(a->w.flr.cur_x * TEX_W) % TEX_W;
		a->w.flr.text_y = (int)(a->w.flr.cur_y * TEX_H) % TEX_H;
		a->w.tex_col = &((Uint8*)(a->w.sdl->surfaces[19]->pixels))[TEX_W * 3 *
		a->w.flr.text_y + a->w.flr.text_x * 3];
		a->w.color = *(Uint32*)(a->w.tex_col);
		a->w.color = (a->w.color >> 2) & 0x7F7F7F;
		a->w.sdl->pixels[a->t1 + (a->w.y * WIN_WIDTH)] = a->w.color;
		a->w.tex_col = &((Uint8*)(a->w.sdl->surfaces[18]->pixels))[TEX_W * 3 *
		a->w.flr.text_y + a->w.flr.text_x * 3];
		a->w.color = *(Uint32*)(a->w.tex_col);
		a->w.sdl->pixels[a->t1 + ((WIN_HEIGHT - a->w.y) \
		* WIN_WIDTH)] = a->w.color;
		a->w.y++;
	}
}
