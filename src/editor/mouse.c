/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:06:08 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/10 20:51:14 by dorange-         ###   ########.fr       */
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
	if (ft_editor_check_mouse_vertex_pos(w, x, y))
		w->mouse_vertex = (t_vector3){(20 + (x + E_GRID_V_D - 20) / E_GRID_L * E_GRID_L), (20 + (y + E_GRID_V_D - 20) / E_GRID_L * E_GRID_L), 0, 1};
	else
		w->mouse_vertex = (t_vector3){0, 0, 0, 0};
}

void	ft_editor_sector_create(t_wolf3d *w)
{
	t_sector	*sector;
	t_list		*list_item;

	sector = ft_my_malloc(sizeof(t_sector));
	// ft_parser_nnmp_sector_param(w, line, sector);
	// ft_parser_nnmp_sector_vertexes(w, line, sector);
	// ft_parser_nnmp_sector_neighborhood(w, line, sector);
	list_item = ft_lstnew(sector, sizeof(t_sector));
	if (w->sector == NULL)
		w->sector = list_item;
	else
		ft_lstadd(&(w->sector), list_item);
}

void	ft_editor_sector_add_vertex(t_wolf3d *w)
{
	t_sector	*sector;

	sector = w->sector->content;
}

int		ft_editor_sector_compare_vertexes(t_vector3 v1, t_vector3 v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v1.w)
		return (1);
	return (0);
}

void	ft_editor_mouse_click(t_wolf3d *w, SDL_Event e)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	SDL_GetMouseState(&x, &y);
	if (ft_editor_check_mouse_vertex_pos(w, x, y))
	{
		if (w->sector_status == 0)
		{
			w->sector_status = 1;
			ft_editor_sector_create(w);
			// if (ft_editor_sector_compare_vertexes())
		}
		
		// if (w->sector == NULL)
	}
}