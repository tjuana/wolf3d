/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:06:08 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/10 20:11:24 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_editor_mouse_move(t_wolf3d *w, SDL_Event e)
{
	int			x;
	int			y;
	int			x_s;
	int			y_s;

	x = 0;
	y = 0;
	SDL_GetMouseState(&x, &y);
	if ((x < 0 || x >= WIN_WIDTH) ||
		(y < 0 || y >= WIN_HEIGHT))
		return ;
	x_s = ((int)(x - 20) % E_GRID_L);
	y_s = ((int)(y - 20) % E_GRID_L);
	if ((x_s < E_GRID_V_D || x_s > E_GRID_L - E_GRID_V_D) && (y_s < E_GRID_V_D || y_s > E_GRID_L - E_GRID_V_D))
		w->mouse_vertex = (t_vector3){(20 + (x + E_GRID_V_D - 20) / E_GRID_L * E_GRID_L), (20 + (y + E_GRID_V_D - 20) / E_GRID_L * E_GRID_L), 0, 1};
	else
		w->mouse_vertex = (t_vector3){0, 0, 0, 0};
}