/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 16:27:33 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/05 18:07:17 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
	void ft_check_walls_vertex_cross(t_wolf3d *w, t_sector *ptr_sector)

	I don't know how to name this function correctly, but
	this is function that search number of intersections with a sector.
*/
int		ft_check_walls_vertex_cross(t_wolf3d *w, t_sector *ptr_sector)
{
	int				i;
	int				vtx1_n; // vertex number
	int				vtx2_n;
	t_vector3		p;
	int				count;

	i = 0;
	count = 0;
	while (i < ptr_sector->vertex_count)
	{
		// printf("CHECK -%d\n", i);
		vtx1_n = i;
		vtx2_n = i + 1;
		if (vtx2_n == ptr_sector->vertex_count)
			vtx2_n = 0;

		if (!ft_check_div(
			0.0,
			0.0,
			w->pl.pos.x,
			w->pl.pos.y,
			ptr_sector->vertex[vtx1_n]->x,
			ptr_sector->vertex[vtx1_n]->y,
			ptr_sector->vertex[vtx2_n]->x,
			ptr_sector->vertex[vtx2_n]->y
		))
		{
			i++;
			continue;
		}
		
		p = ft_find_intersect(
			0.0,
			0.0,
			w->pl.pos.x,
			w->pl.pos.y,
			ptr_sector->vertex[vtx1_n]->x,
			ptr_sector->vertex[vtx1_n]->y,
			ptr_sector->vertex[vtx2_n]->x,
			ptr_sector->vertex[vtx2_n]->y
		);

		if (
			ft_check_point_in_line_segment(p, *ptr_sector->vertex[vtx1_n], *ptr_sector->vertex[vtx2_n]) &&
			ft_check_point_in_line_segment(p, (t_vector3){0.0, 0.0, 0.0, 0.0}, w->pl.pos)			
		)
		{
			printf("P%02d: x_%5.2f, y_%5.2f | ", count + 1, p.x, p.y);
			count++;
		}

		printf("X%02d: x_%5.2f, y_%5.2f | ", count + 1, p.x, p.y);


		i++;
	}

	printf("%d\n", count);

	if (count % 2 == 0)
		return (0);
	return (1);
}

int		ft_get_player_sector(t_wolf3d *w)
{
	t_list		*ptr_list;
	t_sector	*ptr_sector;
	int			i;

	ptr_list = w->sector;
	i = 0;
	while (ptr_list)
	{
		// printf("CHECK %d\n", i);
		ptr_sector = ptr_list->content;

		if (ft_check_walls_vertex_cross(w, ptr_sector))
			return (i + 1);

		ptr_list = ptr_list->next;
		i++;
	}
	return (0);
}
