/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:24:13 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/12 11:52:34 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_editor_fill_frame(t_wolf3d *w)
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
			w->sdl->pixels[x + (y * WIN_WIDTH)] = 0x000000;
			x++;
		}
		y++;
	}
}

int			ft_editor_check_line_for_map(t_vector3 p1, t_vector3 p2)
{
	return (1);
}

/*
	void ft_editor_get_angle(double sin, double cos)

	Funtion that return angle in radians.
*/
double		ft_editor_get_angle(double sin, double cos)
{
	if (sin > 0.0)
		return (acos(cos));
	return (acos(-cos) + M_PI);
}

/*
	void ft_editor_map_transform_vertexes(t_wolf3d *w, t_sector *ptr_sector, t_sector *ptr_sector_origin, double diff)

	Transform map vertex.
*/
void		ft_editor_map_transform_vertexes(t_wolf3d *w, t_sector *ptr_sector, t_sector *ptr_sector_origin, double diff)
{
	int				i;
	double			angle;
	t_matrix_4x4	temp_matrix;

	// Transform map coordinates
	i = 0;
	angle = ft_editor_get_angle(-w->pl.camera_vector.x, -w->pl.camera_vector.y);
	temp_matrix = ft_identify(temp_matrix);
	temp_matrix = ft_rz_matrix(temp_matrix, angle);

	while (i < ptr_sector->vertex_count)
	{
		ptr_sector->vertex[i]->x = ptr_sector_origin->vertex[i]->x - w->pl.pos.x;
		ptr_sector->vertex[i]->y = ptr_sector_origin->vertex[i]->y - w->pl.pos.y;
		ptr_sector->vertex[i]->z = ptr_sector_origin->vertex[i]->z;
			
		*ptr_sector->vertex[i] = ft_transform_vertex(*ptr_sector->vertex[i], temp_matrix);

		// isometric (no)
		ptr_sector->vertex[i]->x *= diff;
		ptr_sector->vertex[i]->y *= diff;

		ptr_sector->vertex[i]->x += w->pl.pos.x;
		ptr_sector->vertex[i]->y += w->pl.pos.y;

		i++;
	}
}

/*
	void ft_editor_map_draw_walls(t_wolf3d *w, t_sector *ptr_sector)

	Draw walls on the map.
*/
void		ft_editor_map_draw_walls(t_wolf3d *w, t_sector *ptr_sector)
{
	int				i;
	t_vector3		c1;
	t_vector3		c2;
	int				vtx1_n; // vertex number
	int				vtx2_n;

	i = 0;
	if (ptr_sector->status == 0)
		ptr_sector->color = 0x7b68ee;
	else
		ptr_sector->color = 0xf8f32b;
	while (i < ptr_sector->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = i + 1;
		if (vtx2_n == ptr_sector->vertex_count)
		{
			if (ptr_sector->status == 1)
				vtx2_n = 0;
			else
				break ;
		}

		// Get line coordinates
		c1 = ft_editor_map_get_xy_vertex_pos(w, *ptr_sector->vertex[vtx1_n]);
		c2 = ft_editor_map_get_xy_vertex_pos(w, *ptr_sector->vertex[vtx2_n]);

		if (ft_editor_check_line_for_map(c1, c2))
			ft_fdf_wu_color(&c1, &c2, w, ptr_sector->color);

		i++;
	}

	i = 0;
	while (i < ptr_sector->vertex_count)
	{
		c1 = ft_editor_map_get_xy_vertex_pos(w, *ptr_sector->vertex[i]);
		ft_editor_draw_point(w, c1, ptr_sector->color);
		i++;
		/*c1 = ft_editor_map_get_xy_vertex_pos(w, *ptr_sector->vertex[vtx1_n]);
		c2 = ft_editor_map_get_xy_vertex_pos(w, *ptr_sector->vertex[vtx2_n]);

		if (ft_editor_check_line_for_map(c1, c2))
			ft_fdf_wu(&c1, &c2, w);*/
	}
}

/*
**	void ft_editor_map_draw_walls_height(t_wolf3d *w, t_sector *ptr_sector, t_sector *ptr_sector_top)
**
**	Function that draw walls height (imitation).
*/
void		ft_editor_map_draw_walls_height(t_wolf3d *w, t_sector *ptr_sector, t_sector *ptr_sector_top)
{
	int		i;
	t_vector3		c1;
	t_vector3		c2;

	i = 0;
	while (i < ptr_sector->vertex_count)
	{
		c1.x = ptr_sector->vertex[i]->x * 16 - (w->pl.pos.x - 8) * 16 + w->view_map.place.x;
		c1.y = ptr_sector->vertex[i]->y * 16 - (w->pl.pos.y - 8) * 16 + w->view_map.place.y;
		c2.x = ptr_sector_top->vertex[i]->x * 16 - (w->pl.pos.x - 8) * 16 + w->view_map.place.x;
		c2.y = ptr_sector_top->vertex[i]->y * 16 - (w->pl.pos.y - 8) * 16 + w->view_map.place.y;

		if (ft_editor_check_line_for_map(c1, c2))
			ft_fdf_wu(&c1, &c2, w);

		i++;
	}
}

void		ft_editor_draw_map_2d(t_wolf3d *w, t_list *sector)
{
	if (sector)
	{
		ft_editor_draw_map_2d(w, sector->next);
		ft_editor_map_draw_walls(w, (t_sector*)sector->content);
	}
}
