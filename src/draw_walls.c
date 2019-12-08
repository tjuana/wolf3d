/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:01:59 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/08 16:26:54 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			ft_wall_hit_switch(t_threads *a)
{
	if (a->w.pl.side == 0)
		a->w.pl.wall_dist = (a->w.map.x - a->w.pl.pos.x +\
		((1 - a->w.pl.stepx) >> 1)) / a->w.pl.raydir.x;
	else
		a->w.pl.wall_dist = (a->w.map.y - a->w.pl.pos.y +\
		((1 - a->w.pl.stepy) >> 1)) / a->w.pl.raydir.y;
	a->w.line_height = (int)(WIN_HEIGHT / a->w.pl.wall_dist);
}

void				ft_wall_hit(t_threads *a)
{
	a->w.hit = 0;
	while (a->w.hit == 0)
	{
		if (a->w.pl.side_dist.x < a->w.pl.side_dist.y)
		{
			a->w.pl.side_dist.x += a->w.pl.delta_dist.x;
			a->w.map.x += a->w.pl.stepx;
			a->w.pl.side = 0;
		}
		else
		{
			a->w.pl.side_dist.y += a->w.pl.delta_dist.y;
			a->w.map.y += a->w.pl.stepy;
			a->w.pl.side = 1;
		}
		if (a->w.map.map[a->w.map.x + a->w.map.y * a->w.map.m_wid] > 0\
		&& a->w.map.map[a->w.map.x + a->w.map.y * a->w.map.m_wid] < 21)
			a->w.hit = 1;
	}
	ft_wall_hit_switch(a);
}

void				ft_wall_draw_start(t_threads *a)
{
	a->w.draw_start = a->w.half_height - (a->w.line_height >> 1);
	a->w.draw_end = (a->w.line_height >> 1) + a->w.half_height;
	a->w.draw_start += a->w.mouse_offset;
	a->w.draw_end += a->w.mouse_offset;
	a->w.draw_start < 0 ? a->w.draw_start = 0 : 0;
	a->w.draw_end >= WIN_HEIGHT ? a->w.draw_end = WIN_HEIGHT - 1 : 0;
	a->w.texture_num =\
	a->w.map.map[a->w.map.x + a->w.map.y * a->w.map.m_wid] - 1;
	if (a->w.pl.side == 0)
		a->w.wall_hit = a->w.pl.pos.y + a->w.pl.wall_dist * a->w.pl.raydir.y;
	else
		a->w.wall_hit = a->w.pl.pos.x + a->w.pl.wall_dist * a->w.pl.raydir.x;
	a->w.wall_hit -= floor(a->w.wall_hit);
	a->w.text_x = (int)(a->w.wall_hit * (double)(TEX_W));
	if (a->w.pl.side == 0 && a->w.pl.raydir.x > 0)
		a->w.text_x = TEX_W - a->w.text_x - 1;
	if (a->w.pl.side == 1 && a->w.pl.raydir.y < 0)
		a->w.text_x = TEX_W - a->w.text_x - 1;
}

void				ft_draw_walls(t_threads *a)
{
	a->w.y = a->w.draw_start;
	while (a->w.y < a->w.draw_end)
	{
		a->w.temp = (a->w.y << 8) - (WIN_HEIGHT << 7) + (a->w.line_height << 7);
		a->w.text_y = (((a->w.temp * TEX_H) / a->w.line_height) >> 8);
		a->w.tex_col = &((Uint8*)(a->w.sdl->surfaces\
		[a->w.texture_num]->pixels))[TEX_H * 3 * a->w.text_y + a->w.text_x * 3];
		a->w.color = *(Uint32*)(a->w.tex_col);
		if (a->w.pl.side == 1)
			a->w.color = (a->w.color >> 1) & 0x7F7F7F;
		a->w.sdl->pixels[a->t1 + (a->w.y * WIN_WIDTH)] = a->w.color;
		a->w.y++;
	}
	a->w.z_buffer[a->t1] = a->w.pl.wall_dist;
}
