/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:06:08 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/11 12:40:29 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_editor_check_mouse_vertex_pos(t_wolf3d *w, int x, int y)
{
	int			x_s;
	int			y_s;

	SDL_GetMouseState(&x, &y);
	if ((x < 0 || x >= WIN_WIDTH) ||
		(y < 0 || y >= WIN_HEIGHT))
		return (0);
	x_s = ((int)(x - 20) % E_GRID_L);
	y_s = ((int)(y - 20) % E_GRID_L);
	if ((x_s < E_GRID_V_D || x_s > E_GRID_L - E_GRID_V_D) && \
		(y_s < E_GRID_V_D || y_s > E_GRID_L - E_GRID_V_D))
		return (1);
	return (0);
}

void	ft_editor_mouse_move(t_wolf3d *w, SDL_Event e)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	SDL_GetMouseState(&x, &y);
	w->mouse_pos = (t_vector3){x, y, 0, 0};
	if (ft_editor_check_mouse_vertex_pos(w, x, y))
		w->mouse_vertex = (t_vector3){(20 + (x + E_GRID_V_D - 20) / E_GRID_L * E_GRID_L), (20 + (y + E_GRID_V_D - 20) / E_GRID_L * E_GRID_L), 0, 1};
	else
		w->mouse_vertex = (t_vector3){0, 0, 0, 0};
}

void	ft_editor_sector_set_vertex(t_wolf3d *w, t_sector *sector, t_vector3 v)
{
	t_vector3	**vertex;
	t_vector3	*p;
	int			i;

	vertex = ft_my_malloc(sizeof(void*) * sector->vertex_count + 1);
	i = 0;
	while (i < sector->vertex_count)
	{
		vertex[i] = sector->vertex[i];
		i++;
	}
	p = malloc(sizeof(t_vector3));
	ft_bzero(p, sizeof(t_vector3));
	*p = v;
	vertex[i] = p;
	free(sector->vertex);
	sector->vertex = vertex;
	sector->vertex_count++;
}

void	ft_editor_sector_create(t_wolf3d *w)
{
	t_sector	*sector;
	t_list		*list_item;

	sector = ft_my_malloc(sizeof(t_sector));
	sector->vertex = NULL;
	sector->vertex_count = 0;
	list_item = ft_lstnew(sector, sizeof(t_sector));
	if (w->sector == NULL)
		w->sector = list_item;
	else
		ft_lstadd(&(w->sector), list_item);
}

int		ft_editor_sector_compare_vertexes(t_vector3 v1, t_vector3 v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v1.w)
		return (1);
	return (0);
}

void	ft_editor_sector_draw_line_to_vertex(t_wolf3d *w)
{
	t_sector	*sector;
	t_vector3	c;

	sector = w->sector->content;
	c = ft_editor_map_get_xy_vertex_pos(w, *sector->vertex[sector->vertex_count - 1]);
	if (w->mouse_vertex.w == 1)
	{
		ft_fdf_wu_color(&w->mouse_vertex, &c, w, 0xCCCCCC);
	}
	else
		ft_fdf_wu_color(&(t_vector3){w->mouse_pos.x, w->mouse_pos.y, 0, 0}, &c, w, 0xCCCCCC);
}

void	ft_editor_mouse_click(t_wolf3d *w, SDL_Event e)
{
	int			x;
	int			y;
	int			x_c;
	int			y_c;
	t_sector	*sector;

	x = 0;
	y = 0;
	SDL_GetMouseState(&x, &y);
	if (ft_editor_check_mouse_vertex_pos(w, x, y))
	{
		if (w->sector_status == 0)
		{
			w->sector_status = 1;
			ft_editor_sector_create(w);
		}
		x_c = (int)((x + E_GRID_V_D - 20) / E_GRID_L);
		y_c = (int)((y + E_GRID_V_D - 20) / E_GRID_L);

		ft_editor_sector_set_vertex(w, w->sector->content, (t_vector3){x_c, y_c, 0, 0});

		sector = w->sector->content;
		if (sector->vertex_count > 1 && ft_editor_sector_compare_vertexes(*sector->vertex[0], *sector->vertex[sector->vertex_count - 1]))
		{
			sector->status = 1;
			w->sector_status = 0;
		}

		printf("===\n");
		ft_print_sectors(w->sector);
	}
}