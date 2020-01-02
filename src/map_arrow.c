/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_arrow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:24:36 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/02 15:09:07 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_draw_compass_static(t_wolf3d *w)
{
	// Исправленная стрека
	t_vector3		c1;
	t_vector3		c2;
	double		offset_x;
	double		offset_y;

	offset_x = w->view_map.place.x + 128;
	offset_y = w->view_map.place.y + 128;

	// Первая линия
	c1.x = offset_x + (0) * 10;
	c1.y = offset_y + (-1) * 10;
	c2.x = offset_x - (0) * 10;
	c2.y = offset_y - (-1) * 10;
	ft_fdf_wu(&c1, &c2, w);

	// Вторая линия
	c1.x = offset_x + (0) * 10;
	c1.y = offset_y + (-1) * 10;
	c2.x = offset_x - (0 * cos(1) + -1 * sin(0.5)) * 10;
	c2.y = offset_y - (-1 * cos(1) - 0 * sin(0.5)) * 10;
	ft_fdf_wu(&c1, &c2, w);

	// Третья линия (-)
	c1.x = offset_x + (0) * 10;
	c1.y = offset_y + (-1) * 10;
	c2.x = offset_x - (0 * cos(1) - -1 * sin(0.5)) * 10;
	c2.y = offset_y - (-1 * cos(1) + 0 * sin(0.5)) * 10;
	ft_fdf_wu(&c1, &c2, w);
}

static void		ft_draw_compass_arrow(t_wolf3d *w)
{
	// Исправленная стрека
	t_vector3		c1;
	t_vector3		c2;
	double		offset_x;
	double		offset_y;

	offset_x = w->view_map.place.x + 128;
	offset_y = w->view_map.place.y + 128;

	// Первая линия
	c1.x = offset_x + (w->pl.camera_vector.x) * 10;
	c1.y = offset_y + (w->pl.camera_vector.y) * 10;
	c2.x = offset_x - (w->pl.camera_vector.x) * 10;
	c2.y = offset_y - (w->pl.camera_vector.y) * 10;
	ft_fdf_wu(&c1, &c2, w);

	// Вторая линия
	c1.x = offset_x + (w->pl.camera_vector.x) * 10;
	c1.y = offset_y + (w->pl.camera_vector.y) * 10;
	c2.x = offset_x - (w->pl.camera_vector.x * cos(1) + w->pl.camera_vector.y * sin(0.5)) * 10;
	c2.y = offset_y - (w->pl.camera_vector.y * cos(1) - w->pl.camera_vector.x * sin(0.5)) * 10;
	ft_fdf_wu(&c1, &c2, w);

	// Третья линия (-)
	c1.x = offset_x + (w->pl.camera_vector.x) * 10;
	c1.y = offset_y + (w->pl.camera_vector.y) * 10;
	c2.x = offset_x - (w->pl.camera_vector.x * cos(1) - w->pl.camera_vector.y * sin(0.5)) * 10;
	c2.y = offset_y - (w->pl.camera_vector.y * cos(1) + w->pl.camera_vector.x * sin(0.5)) * 10;
	ft_fdf_wu(&c1, &c2, w);
}

void			ft_draw_compass(t_wolf3d *w)
{
	ft_draw_compass_arrow(w);
}
