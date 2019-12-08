/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:24:13 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/29 14:12:32 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_init_view_map(t_wolf3d *wolf)
{
	wolf->view_map.frame = 0;
	wolf->view_map.pframe.size = (t_coord){256, 256};
	wolf->view_map.place = (t_coord){0, WIN_HEIGHT - 256};
	return (0);
}

static int	ft_check_map_pos(t_wolf3d *w, int pos, int x, int y)
{
	return (pos > w->map.m_wid * w->map.m_hei || pos < 0 ||
		floor(((y - w->view_map.place.y) / 32) \
			+ w->pl.pos.y - 4) >= w->map.m_hei ||
		floor(((x - w->view_map.place.x) / 32) \
		+ w->pl.pos.x - 4) >= w->map.m_wid ||
		floor(((y - w->view_map.place.y) / 32) \
			+ w->pl.pos.y - 4) < 0 ||
		floor(((x - w->view_map.place.x) / 32) \
		+ w->pl.pos.x - 4) < 0);
}

static void		ft_draw_map_text(t_wolf3d *w, int pos, int x, int y)
{
	int		pixel_pos;

	pixel_pos = (int)(y - w->view_map.place.y \
		+ (w->pl.pos.y - 4) * 32) % 32 * TEX_H * 3 * 2
		+ (int)(x - w->view_map.place.x \
		+ (w->pl.pos.x - 4) * 32) % 32 * 3 * 2;
	if (pixel_pos >= 0 || pixel_pos < TEX_W * TEX_H)
	{
		w->tex_col = &((Uint8 *)(w->sdl->surfaces\
			[w->map.map[pos] - 1]->pixels))[pixel_pos];
		w->color = *(Uint32 *)w->tex_col;
		w->color &= 0xFFFFFF;
		if (w->color != 0xFF00FF)
			w->sdl->pixels[-x + (y * WIN_WIDTH)] = w->color;
	}
}

static int	pos_calc(t_wolf3d *w, int x, int y)
{
	return ((int)(floor(((y - w->view_map.place.y) / 32) \
				+ w->pl.pos.y - 4) * w->map.m_wid +
				floor(((x - w->view_map.place.x) / 32) \
				+ w->pl.pos.x - 4)));
}

void		ft_draw_map(t_wolf3d *w)//draw the black part of the map
{
	int		x;
	int		y;
	int		pos;

	y = w->view_map.place.y;
	while (y < w->view_map.pframe.size.y + w->view_map.place.y)
	{
		x = w->view_map.place.x;
		while (x < w->view_map.pframe.size.x + w->view_map.place.x)
		{
			pos = pos_calc(w, x, y);
			if (ft_check_map_pos(w, pos, x, y))
				w->sdl->pixels[-x + (y * WIN_WIDTH) - 1] = 0x00ff00;//out view of the map
			else
			{
				if (w->map.map[pos] != 0)
					ft_draw_map_text(w, pos, x, y);
				else
					w->sdl->pixels[-x + (y * WIN_WIDTH) - 1] = 0x000000;
			}
			x++;
		}
		y++;
	}
	ft_draw_compass(w);
}
