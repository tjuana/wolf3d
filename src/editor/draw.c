/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:26:48 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/10 20:13:06 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_editor_draw_point(t_wolf3d *data, t_vector3 v, int color)
{
	int	i;
	int	j;

	// printf("%d %d\n", (int)v.x, (int)v.y);
	i = (int)v.x - E_GRID_V_D_D;
	while (i < (int)v.x + E_GRID_V_D_D)
	{
		j = (int)v.y - E_GRID_V_D_D;
		while (j < (int)v.y + E_GRID_V_D_D)
		{
			data->sdl->pixels[i + j * WIN_WIDTH] = color;
			j++;
		}
		i++;
	}
}

void	ft_editor_draw_mouse_vertex(t_wolf3d *w)
{
	if (w->mouse_vertex.w == 1)
		ft_editor_draw_point(w, w->mouse_vertex, 0xff0000);
}