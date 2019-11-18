/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_arrow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:24:36 by dorange-          #+#    #+#             */
/*   Updated: 2019/11/14 17:46:46 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ft_draw_compass_arrow(t_wolf3d *w)
{
	t_coord		c1;
	t_coord		c2;

	c1.x = w->view_map.place.x + 128 + (w->pl.dir.x) * 10;
	c1.y = w->view_map.place.y + 128 + (w->pl.dir.y) * 10;
	c2.x = w->view_map.place.x + 128 - (w->pl.dir.x) * 10;
	c2.y = w->view_map.place.y + 128 - (w->pl.dir.y) * 10;
	ft_fdf_wu(&c1, &c2, w);
	c1.x = w->view_map.place.x + 128 + (w->pl.dir.x) * 10;
	c1.y = w->view_map.place.y + 128 + (w->pl.dir.y) * 10;
	c2.x = w->view_map.place.x + 128 - (w->pl.dir.x) * 10 - 10 \
		* cos(atan(w->pl.dir.y / w->pl.dir.x) - 1);
	c2.y = w->view_map.place.y + 128 - (w->pl.dir.y) * 10 - 10 \
		* sin(atan(w->pl.dir.y / fabs(w->pl.dir.x)) - 1);
	ft_fdf_wu(&c1, &c2, w);
	c1.x = w->view_map.place.x + 128 + (w->pl.dir.x) * 10;
	c1.y = w->view_map.place.y + 128 + (w->pl.dir.y) * 10;
	c2.x = w->view_map.place.x + 128 - (w->pl.dir.x) * 10 - 10 \
		* cos(atan(w->pl.dir.y / w->pl.dir.x) + 1);
	c2.y = w->view_map.place.y + 128 - (w->pl.dir.y) * 10 - 10 \
		* sin(atan(w->pl.dir.y / fabs(w->pl.dir.x)) + 1);
	ft_fdf_wu(&c1, &c2, w);
}

void			ft_draw_compass(t_wolf3d *w)
{
	int			x;
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
	}
	ft_draw_compass_arrow(w);
}
