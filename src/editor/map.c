/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:24:13 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/11 11:23:16 by dorange-         ###   ########.fr       */
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

t_vector3	ft_editor_map_get_xy_vertex_pos(t_wolf3d *w, t_vector3 v)
{
	int			grid_l;
	t_vector3	indent;

	grid_l = 32;
	indent = (t_vector3){20, 20, 0, 0};

	return ((t_vector3){
		v.x * grid_l + indent.x,
		v.y * grid_l + indent.y,
		0, 0
	});
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
			ft_fdf_wu(&c1, &c2, w);

		i++;
	}

	i = 0;
	while (i < ptr_sector->vertex_count)
	{
		c1 = ft_editor_map_get_xy_vertex_pos(w, *ptr_sector->vertex[i]);
		ft_editor_draw_point(w, c1, 0xffff00);
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

/*
	void ft_editor_draw_walls_for_map(t_wolf3d *w, t_sector *ptr_sector, t_sector *ptr_sector_origin)

	New function that draw walls for map.
*/
void		ft_editor_draw_walls_for_map(t_wolf3d *w, t_sector *ptr_sector, t_sector *ptr_sector_top, t_sector *ptr_sector_origin)
{
	int				i;
	t_vector3		c1;
	t_vector3		c2;
	double			angle;
	t_matrix_4x4	temp_matrix;

	ft_editor_map_draw_walls(w, ptr_sector);
}

/*
	void ft_draw_map_new_sector(t_wolf3d *w)

	Function that draw new maps (sector).
*/
void		ft_editor_draw_map_new_sector_iso(t_wolf3d *w)
{
	t_list			*ptr_list;
	t_list			*ptr_list_top;
	t_list			*ptr_list_origin;
	t_sector		*ptr_sector;
	t_sector		*ptr_sector_top;
	t_sector		*ptr_sector_origin;

	// ft_editor_fill_frame(w);
	ptr_list = w->sector;
	ptr_list_top = w->map_sector_top;
	ptr_list_origin = w->sector;
	while (ptr_list)
	{
		// Get line values
		ptr_sector = (t_sector*)ptr_list->content;
		ptr_sector_origin = (t_sector*)ptr_list_origin->content;
		ptr_sector_top = (t_sector*)ptr_list_top->content;

		ft_editor_draw_walls_for_map(w, ptr_sector, ptr_sector_top, ptr_sector_origin);

		ptr_list = ptr_list->next;
		ptr_list_top = ptr_list_top->next;
		ptr_list_origin = ptr_list_origin->next;
	}
}
