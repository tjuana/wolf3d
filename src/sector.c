/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 16:27:33 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/12 11:36:11 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
	void ft_check_walls_vertex_cross(t_wolf3d *w, t_sector *ptr_sector)

	I don't know how to name this function correctly, but
	this is function that search number of intersections with a sector.
*/
int		ft_check_walls_vertex_cross(t_wolf3d *w, t_sector *ptr_sector, t_vector3 v)
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
			v.x,
			v.y,
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
			v.x,
			v.y,
			ptr_sector->vertex[vtx1_n]->x,
			ptr_sector->vertex[vtx1_n]->y,
			ptr_sector->vertex[vtx2_n]->x,
			ptr_sector->vertex[vtx2_n]->y
		);

		if (
			ft_check_point_in_line_segment(p, *ptr_sector->vertex[vtx1_n], *ptr_sector->vertex[vtx2_n]) &&
			ft_check_point_in_line_segment(p, (t_vector3){0.0, 0.0, 0.0, 0.0}, v)
			//!ft_check_point_in_line_segment(p, *ptr_sector->vertex[0], w->pl.pos)
		)
		{
			count++;
		}

		i++;
	}

	if (count % 2 == 0)
		return (0);
	return (1);
}

int		ft_editor_sector_compare_vertexes(t_vector3 v1, t_vector3 v2)
{
	if ((int)v1.x == (int)v2.x && (int)v1.y == (int)v2.y && (int)v1.z == (int)v2.z)
		return (1);
	return (0);
}

int		ft_sector_check_cross(t_wolf3d *w, t_sector *ptr_sector, t_vector3 v)
{
	int				i;
	int				vtx1_n; // vertex number
	int				vtx2_n;
	t_vector3		p;
	int				count;

	t_vector3		vertex3;
	t_vector3		vertex4;
	t_vector3		vertex5;

	t_sector		*sector;

	int				m;

	i = 0;
	count = 0;
	m = 0;
	while (i < ptr_sector->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = i + 1;
		if (vtx2_n == ptr_sector->vertex_count)
			vtx2_n = 0;

		vertex3 = ft_editor_map_get_xy_vertex_pos(w, *ptr_sector->vertex[vtx1_n]);
		vertex4 = ft_editor_map_get_xy_vertex_pos(w, *ptr_sector->vertex[vtx2_n]);

		if (ft_editor_sector_compare_vertexes(v, vertex3) || ft_editor_sector_compare_vertexes(v, vertex4))
		{
			// sector = (t_sector*)(w->sector->content);
			// if (sector->status == 0)
			// {
			// 	// Проверяем, не лежит ли прямая внутри сектора
			// 	vertex5 = (t_vector3){
			// 		(sector->vertex[sector->vertex_count - 1]->x + v.x) / 2, \
			// 		(sector->vertex[sector->vertex_count - 1]->y + v.y) / 2, \
			// 		0, 0
			// 	};
			// 	// Скорее всего, нужно добавить рекурсию.
			// 	// > ввести для ft_sector_check_cross разные returns:
			// 	// 0: нет пересечений, 1: точка внутри сектора, 2: есть точка на линии

			// 	return (1);
			// }
			// else
				return (0);
		}

		if (ft_check_point_in_line_segment(v, vertex3, vertex4))
			return (2);

		// debug
		// printf("%f   %f   %f   %f   %f   %f   %f   %f\n", 0.0, 0.0, v.x, v.y, vertex3.x, vertex3.y, vertex4.x, vertex4.y);

		if (!ft_check_div(
			0.0,
			0.0,
			v.x,
			v.y,
			vertex3.x,
			vertex3.y,
			vertex4.x,
			vertex4.y
		))
		{
			// count++;
			i++;
			continue;
		}
		
		p = ft_find_intersect(
			0.0,
			0.0,
			v.x,
			v.y,
			vertex3.x,
			vertex3.y,
			vertex4.x,
			vertex4.y
		);

		if (
			ft_check_point_in_line_segment(p, vertex3, vertex4) &&
			ft_check_point_in_line_segment(p, (t_vector3){0.0, 0.0, 0.0, 0.0}, v)
			//!ft_check_point_in_line_segment(p, *ptr_sector->vertex[0], w->pl.pos)
		)
		{
			count++;
		}

		i++;
	}

	// printf("count: %d\n", count);

	if (count % 2 == 0)
		return (0);
	return (1);
}

int		ft_sector_check_sector(t_wolf3d *w)
{
	t_list		*ptr_list;
	t_sector	*ptr_sector;
	int			i;

	// printf("check...\n");
	ptr_list = w->sector;
	i = 0;
	while (ptr_list)
	{
		ptr_sector = ptr_list->content;

		if (ptr_sector->status == 0)
		{
			ptr_list = ptr_list->next;
			i++;
			continue ;
		}
		// printf("CHECK SECTOR #%d\n", i);

		if (ft_sector_check_cross(w, ptr_sector, w->mouse_pos))
			return (i + 1);

		ptr_list = ptr_list->next;
		i++;
	}
	return (0);
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

		if (ft_check_walls_vertex_cross(w, ptr_sector, w->pl.pos))
			return (i + 1);

		ptr_list = ptr_list->next;
		i++;
	}
	return (0);
}

/*
	double ft_sector_get_player_wall_length(t_threads *a, t_sector *sector, int line_numb)

	Function that return length between player and wall.
*/
double	ft_sector_get_player_wall_length(t_threads *a, t_sector *sector, int line_numb)
{
	t_vector3	p;
	t_vector3	p1;
	t_vector3	p2;
	// vector (temp)
	t_vector3	p1_pl;
	t_vector3	p2_pl;
	double		l;

	// Get line
	p1 = *sector->vertex[line_numb];
	if (line_numb + 1 == sector->vertex_count)
		p2 = *sector->vertex[0];
	else
		p2 = *sector->vertex[line_numb + 1];

	// Calculation
	// Проверка, что делитель не 0
	if (!ft_check_div(
		a->w.pl.pos.x,
		a->w.pl.pos.y,
		(a->w.pl.pos.x + a->w.fc_dir.x),
		(a->w.pl.pos.y + a->w.fc_dir.y), 
		p1.x,
		p1.y,
		p2.x,
		p2.y
	))
		return (0);

	p = ft_find_intersect(
		a->w.pl.pos.x,
		a->w.pl.pos.y,
		(a->w.pl.pos.x + a->w.fc_dir.x),
		(a->w.pl.pos.y + a->w.fc_dir.y), 
		p1.x,
		p1.y,
		p2.x,
		p2.y
	);

	// Вектор 
	p1_pl.x = a->w.pl.pos.x;
	p1_pl.y = a->w.pl.pos.y;
	p2_pl.x = (a->w.pl.pos.x + a->w.fc_dir.x);
	p2_pl.y = (a->w.pl.pos.y + a->w.fc_dir.y);

	if (!ft_check_point(p, p1, p2, p1_pl, p2_pl))
		return (0);

	// Расстояние от точки пересечения до позиции игрока
	l = sqrt(pow((p.x - a->w.pl.pos.x), 2) + pow((p.y - a->w.pl.pos.y), 2));

	// Убираем эффект рыбьего глаза
	l *= (a->w.fc_dir.x * a->w.pl.camera_vector.x + a->w.fc_dir.y * a->w.pl.camera_vector.y);
	return (l);
}

/*
	void ft_sector_sort_double_array_asc(double *array)

	Function that sort double array.
*/
double	*ft_sector_sort_double_array_asc(double *array, int count)
{
	double	temp;
	int		i;
	int		j;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (array[i] > array[j] || array[i] == 0.0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (array);
}

/*
	void ft_sector_draw_vline(t_threads *a, int color)

	Function that draw vline for sector.
*/
void	ft_sector_draw_vline(t_threads *a, int color)
{
	Uint32	i;
	a->w.y = a->w.draw_start;
	while (a->w.y < a->w.draw_end)
	{
		//a->w.wall_color
		a->w.sdl->pixels[a->t1 + (a->w.y * WIN_WIDTH)] = color;
		// a->w.sdl->pixels[a->t1 + (a->w.y * WIN_WIDTH)] = 0x120a8f;
		a->w.y++;
	}
	a->w.z_buffer[a->t1] = a->w.pl.wall_dist;
}

/*
	void ft_sector_calculate_vline(t_threads *a, t_sector *sector, double *length_array)

	Function that calculate and draw wall, floor and ceiling height.
*/
void	ft_sector_calculate_vline(t_threads *a, t_sector *sector, double *length_array)
{
	int		i;
	double	temp_l;

	i = 0;
	temp_l = length_array[i];

	while (temp_l != 0.0)
	{

		if (i % 2)
		{
			// This is floor and ceiling
			a->w.line_height = sector->height * a->w.l_p / (temp_l * (WIN_HEIGHT));
			a->w.draw_end = a->w.draw_start;
			a->w.draw_start = ((int)(a->w.pl.cameraH * WIN_HEIGHT) * a->w.l_p / (temp_l * (WIN_HEIGHT)) + WIN_HEIGHT * a->w.pl.camera_vector.z) - a->w.line_height;
			// check...
			a->w.draw_end >= WIN_HEIGHT ? a->w.draw_end = WIN_HEIGHT - 1 : 0;
			a->w.draw_start < 0 ? a->w.draw_start = 0 : 0;
			ft_sector_draw_vline(a, 0xffffff);
		}
		else
		{
			// This is wall draw
			a->w.line_height = sector->height * a->w.l_p / (temp_l * (WIN_HEIGHT));
			a->w.draw_end = (int)(a->w.pl.cameraH * WIN_HEIGHT) * a->w.l_p / (temp_l * (WIN_HEIGHT)) + WIN_HEIGHT * a->w.pl.camera_vector.z;
			a->w.draw_start = a->w.draw_end - a->w.line_height;
			a->w.draw_end >= WIN_HEIGHT ? a->w.draw_end = WIN_HEIGHT - 1 : 0;
			a->w.draw_start < 0 ? a->w.draw_start = 0 : 0;
			ft_sector_draw_vline(a, sector->color);
		}
		temp_l = length_array[++i];
	}
}

/*
	void ft_sector_cast(t_threads *a)

	Function that draw sector.
*/
void	ft_sector_cast(t_threads *a, t_sector *sector)
{
	double	*l;
	int		i;
	int		count;


	l = ft_my_malloc(sizeof(double) * sector->vertex_count);
	i = 0;
	while (i < sector->vertex_count)
	{
		l[i] = ft_sector_get_player_wall_length(a, sector, i);
		i++;
	}

	l = ft_sector_sort_double_array_asc(l, sector->vertex_count);
	ft_sector_calculate_vline(a, sector, l);
}

/*
	void ft_sector_list_cast(t_threads *a)

	Function that draw sectors.
*/
void	ft_sector_list_cast(t_threads *a)
{
	t_list		*ptr_sector_list;
	t_sector	*ptr_sector;

	// const. for vline
	a->w.pl.cameraX = a->t1 * a->w.camera_x_cnst - 1;
	a->w.fc_dir.x = a->w.pl.camera_vector.x * cos(a->w.pl.cameraX * (a->w.fov / 2)) - a->w.pl.camera_vector.y * sin(a->w.pl.cameraX * (a->w.fov / 2));
	a->w.fc_dir.y = a->w.pl.camera_vector.y * cos(a->w.pl.cameraX * (a->w.fov / 2)) + a->w.pl.camera_vector.x * sin(a->w.pl.cameraX * (a->w.fov / 2));

	ptr_sector_list = a->w.sector;

	while(ptr_sector_list)
	{
		// Работаем с каждым сектором
		ptr_sector = ptr_sector_list->content;

		ft_sector_cast(a, ptr_sector);

		ptr_sector_list = ptr_sector_list->next;
	}
}
