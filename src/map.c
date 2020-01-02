/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:24:13 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/02 19:25:12 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_init_view_map(t_wolf3d *wolf)
{
	wolf->view_map.frame = 0;
	wolf->view_map.pframe.size = (t_vector3){256, 256};
	wolf->view_map.place = (t_vector3){0, WIN_HEIGHT - 256};
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

void		ft_draw_map_text(t_wolf3d *w, int pos, int x, int y)
{
	int		pixel_pos;

	pixel_pos = (int)(y - w->view_map.place.y \
		+ (w->pl.pos.y - 4) * 32) % 32 * TEX_H * 3 * 2
		+ (int)(x - w->view_map.place.x \
		+ (w->pl.pos.x - 4) * 32) % 32 * 3 * 2;
	if (pixel_pos >= 0 || pixel_pos < TEX_W * TEX_H)
	{
		w->tex_col = &((Uint8 *)(w->sdl->textures\
			[w->map.map[pos] - 1]->pixels))[pixel_pos];
		w->color = *(Uint32 *)w->tex_col;
		w->color &= 0xFFFFFF;
		if (w->color != 0xFF00FF)
			w->sdl->pixels[x + (y * WIN_WIDTH)] = w->color;
	}
}

static int	pos_calc(t_wolf3d *w, int x, int y)
{
	return ((int)(floor(((y - w->view_map.place.y) / 32) \
				+ w->pl.pos.y - 4) * w->map.m_wid +
				floor(((x - w->view_map.place.x) / 32) \
				+ w->pl.pos.x - 4)));
}

void		ft_draw_map(t_wolf3d *w)
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
				w->sdl->pixels[x + (y * WIN_WIDTH)] = 0x000000;
			else
			{
				if (w->map.map[pos] != 0)
					ft_draw_map_text(w, pos, x, y);
				else
					w->sdl->pixels[x + (y * WIN_WIDTH)] = 0x000000;
			}
			x++;
		}
		y++;
	}
	ft_draw_compass(w);
}

void		ft_fill_frame(t_wolf3d *w)
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

int			ft_check_line_for_map(t_vector3 p1, t_vector3 p2)
{
	return (1);
}

/*
	void ft_draw_map_new_line(t_wolf3d *w)

	Function that draw new maps (line).
*/
void		ft_draw_map_new_line(t_wolf3d *w)
{
	int		x;
	int		y;
	int		pos;
	t_vector3	c1;
	t_vector3	c2;
	// for list
	t_list	*ptr_list;
	t_line	*ptr_line;
	int		i;

	ft_fill_frame(w);
	ptr_list = w->line;
	i = 0;
	while (ptr_list)
	{
		// Get line values
		ptr_line = (t_line*)ptr_list->content;

		// Get line coordinates
		// Scale and transform
		c1.x = ptr_line->p1.x * 32 - (w->pl.pos.x - 4) * 32 + w->view_map.place.x;
		c1.y = ptr_line->p1.y * 32 - (w->pl.pos.y - 4) * 32 + w->view_map.place.y;
		c2.x = ptr_line->p2.x * 32 - (w->pl.pos.x - 4) * 32 + w->view_map.place.x;
		c2.y = ptr_line->p2.y * 32 - (w->pl.pos.y - 4) * 32 + w->view_map.place.y;

		// Transform points as far as possible (??)
		if(ft_check_line_for_map(c1, c2))
			// Draw line
			ft_fdf_wu(&c1, &c2, w);

		// Get next line
		ptr_list = ptr_list->next;
		i++;
	}


	ft_draw_compass(w);
}

/*
	void ft_draw_map_new_sector(t_wolf3d *w)

	Function that draw new maps (sector).
*/
void		ft_draw_map_new_sector(t_wolf3d *w)
{
	int		x;
	int		y;
	int		pos;
	t_vector3	c1;
	t_vector3	c2;
	// for list
	t_list	*ptr_list;
	t_sector	*ptr_sector;
	int		i;

	ft_fill_frame(w);
	ptr_list = w->sector;
	while (ptr_list)
	{
		// Get line values
		ptr_sector = (t_sector*)ptr_list->content;

		i = 0;
		while ((i + 1) < ptr_sector->vertex_count)
		{
			// Get line coordinates
			// Scale and transform
			c1.x = ptr_sector->vertex[i]->x * 32 - (w->pl.pos.x - 4) * 32 + w->view_map.place.x;
			c1.y = ptr_sector->vertex[i]->y * 32 - (w->pl.pos.y - 4) * 32 + w->view_map.place.y;
			c2.x = ptr_sector->vertex[i + 1]->x * 32 - (w->pl.pos.x - 4) * 32 + w->view_map.place.x;
			c2.y = ptr_sector->vertex[i + 1]->y * 32 - (w->pl.pos.y - 4) * 32 + w->view_map.place.y;
	
			if (ft_check_line_for_map(c1, c2))
				ft_fdf_wu(&c1, &c2, w);
			i++;
		}

		// Last coordinates
		c1.x = ptr_sector->vertex[ptr_sector->vertex_count - 1]->x * 32 - (w->pl.pos.x - 4) * 32 + w->view_map.place.x;
		c1.y = ptr_sector->vertex[ptr_sector->vertex_count - 1]->y * 32 - (w->pl.pos.y - 4) * 32 + w->view_map.place.y;
		c2.x = ptr_sector->vertex[0]->x * 32 - (w->pl.pos.x - 4) * 32 + w->view_map.place.x;
		c2.y = ptr_sector->vertex[0]->y * 32 - (w->pl.pos.y - 4) * 32 + w->view_map.place.y;
	
		if (ft_check_line_for_map(c1, c2))
			ft_fdf_wu(&c1, &c2, w);

		// Get next line
		ptr_list = ptr_list->next;
		i++;
	}

	ft_draw_compass(w);
}

/*
	void ft_get_angle(double sin, double cos)

	Funtion that return angle in radians.
*/
double		ft_get_angle(double sin, double cos)
{
	if (sin > 0.0)
		return (acos(cos));
	return (acos(-cos) + M_PI);
}

/*
	void ft_draw_map_new_sector(t_wolf3d *w)

	Function that draw new maps (sector).
*/
void		ft_draw_map_new_sector_iso(t_wolf3d *w)
{
	int				x;
	int				y;
	int				pos;
	int				i;
	t_vector3		c1;
	t_vector3		c2;
	// for list
	t_list			*ptr_list;
	t_list			*ptr_list_origin;
	t_sector		*ptr_sector;
	t_sector		*ptr_sector_origin;
	// for transform
	t_matrix_4x4	temp_matrix;
	double			angle;

	ft_fill_frame(w);
	ptr_list = w->map_sector;
	ptr_list_origin = w->sector;
	angle = ft_get_angle(-w->pl.camera_vector.x, -w->pl.camera_vector.y);
	while (ptr_list)
	{
		// Get line values
		ptr_sector = (t_sector*)ptr_list->content;
		ptr_sector_origin = (t_sector*)ptr_list_origin->content;

		// Transform map coordinates
		i = 0;
		while (i < ptr_sector->vertex_count)
		{
			// Isometric
			ptr_sector->vertex[i]->x = ptr_sector_origin->vertex[i]->x - w->pl.pos.x;
			ptr_sector->vertex[i]->y = ptr_sector_origin->vertex[i]->y - w->pl.pos.y;
			ptr_sector->vertex[i]->z = ptr_sector_origin->vertex[i]->z;

			temp_matrix = ft_identify(temp_matrix);
			temp_matrix = ft_rz_matrix(temp_matrix, angle);
				
			*ptr_sector->vertex[i] = ft_transform_vertex(*ptr_sector->vertex[i], temp_matrix);

			ptr_sector->vertex[i]->x += w->pl.pos.x;
			ptr_sector->vertex[i]->y += w->pl.pos.y;

			i++;
		}

		i = 0;
		while ((i + 1) < ptr_sector->vertex_count)
		{
			// Get line coordinates
			// Scale and transform
			c1.x = ptr_sector->vertex[i]->x * 16 - (w->pl.pos.x - 8) * 16 + w->view_map.place.x;
			c1.y = ptr_sector->vertex[i]->y * 16 - (w->pl.pos.y - 8) * 16 + w->view_map.place.y;
			c2.x = ptr_sector->vertex[i + 1]->x * 16 - (w->pl.pos.x - 8) * 16 + w->view_map.place.x;
			c2.y = ptr_sector->vertex[i + 1]->y * 16 - (w->pl.pos.y - 8) * 16 + w->view_map.place.y;
	
			if (ft_check_line_for_map(c1, c2))
				ft_fdf_wu(&c1, &c2, w);
			i++;
		}

		// Last coordinates
		c1.x = ptr_sector->vertex[ptr_sector->vertex_count - 1]->x * 16 - (w->pl.pos.x - 8) * 16 + w->view_map.place.x;
		c1.y = ptr_sector->vertex[ptr_sector->vertex_count - 1]->y * 16 - (w->pl.pos.y - 8) * 16 + w->view_map.place.y;
		c2.x = ptr_sector->vertex[0]->x * 16 - (w->pl.pos.x - 8) * 16 + w->view_map.place.x;
		c2.y = ptr_sector->vertex[0]->y * 16 - (w->pl.pos.y - 8) * 16 + w->view_map.place.y;
	
		if (ft_check_line_for_map(c1, c2))
			ft_fdf_wu(&c1, &c2, w);

		// Get next line
		ptr_list = ptr_list->next;
		ptr_list_origin = ptr_list_origin->next;
		i++;
	}

	ft_draw_compass_static(w);
}
