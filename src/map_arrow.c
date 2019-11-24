/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_arrow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:24:36 by dorange-          #+#    #+#             */
/*   Updated: 2019/11/23 17:30:09 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ft_draw_compass_arrow(t_wolf3d *w)
{
	// Исправленная стрека
	t_coord		c1;
	t_coord		c2;
	double		offset_x;
	double		offset_y;

	offset_x = w->view_map.place.x + 128;
	offset_y = w->view_map.place.y + 128;

	// Первая линия
	c1.x = offset_x + (w->pl.dir.x) * 10;
	c1.y = offset_y + (w->pl.dir.y) * 10;
	c2.x = offset_x - (w->pl.dir.x) * 10;
	c2.y = offset_y - (w->pl.dir.y) * 10;
	ft_fdf_wu(&c1, &c2, w);

	// Вторая линия
	c1.x = offset_x + (w->pl.dir.x) * 10;
	c1.y = offset_y + (w->pl.dir.y) * 10;
	c2.x = offset_x - (w->pl.dir.x * cos(1) + w->pl.dir.y * sin(0.5)) * 10;
	c2.y = offset_y - (w->pl.dir.y * cos(1) - w->pl.dir.x * sin(0.5)) * 10;
	ft_fdf_wu(&c1, &c2, w);

	// Третья линия (-)
	c1.x = offset_x + (w->pl.dir.x) * 10;
	c1.y = offset_y + (w->pl.dir.y) * 10;
	c2.x = offset_x - (w->pl.dir.x * cos(1) - w->pl.dir.y * sin(0.5)) * 10;
	c2.y = offset_y - (w->pl.dir.y * cos(1) + w->pl.dir.x * sin(0.5)) * 10;
	ft_fdf_wu(&c1, &c2, w);
}

void			ft_draw_compass(t_wolf3d *w)
{
	/*int			x;
	int			y;

	y = w->view_map.place.y + 127;
	while (y <= w->view_map.place.y + 129)
	{
		x = w->view_map.place.x + 127;
		while (x <= w->view_map.place.x + 129)
		{
			w->sdl->pixels[x + (y * WIN_WIDTH)] = 0xFFFF00;
			x++;
		}
		y++;
	}*/
	ft_draw_compass_arrow(w);
}
