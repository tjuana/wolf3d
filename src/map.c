/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:24:13 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/11 17:48:12 by tjuana           ###   ########.fr       */
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

void		ft_draw_map(t_wolf3d *w)
{
	int x;
	int y;

	y = w->view_map.place.y;
	while (y < w->view_map.pframe.size.y + w->view_map.place.y)
	{
		x = w->view_map.place.x;
		while (x < w->view_map.pframe.size.x + w->view_map.place.x)
		{
			//w->tex_col = &((Uint8 *)(w->map_texture->pixels))[(int)(3 *
			// w->map_texture->w * (y - (int)(w->view_map.place.y) +
			// w->view_map.pframe.cd.y) + (x - (int)(w->view_map.place.x) +
			// w->view_map.pframe.cd.x) * 3)];
			// w->color = *(Uint32 *)w->tex_col;
			// w->color &= 0xFFFFFF;
			w->sdl->pixels[x + (y * WIN_WIDTH)] = 0x00;
			x++;
		}
		y++;
	}
}