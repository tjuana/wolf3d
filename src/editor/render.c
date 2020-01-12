/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:34:19 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/12 11:49:51 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_editor_draw_line(t_wolf3d *w)
{
	int			i;

	i = 20;
	while (i < WIN_HEIGHT - 20)
	{
		ft_fdf_wu_color(&(t_vector3){20, i, 0, 0}, &(t_vector3){WIN_WIDTH - 20, i, 0, 0}, w, 0x444444);
		i += 32;
	}
	i = 20;
	while (i < WIN_WIDTH - 20)
	{
		ft_fdf_wu_color(&(t_vector3){i, 20, 0, 0}, &(t_vector3){i, WIN_HEIGHT - 20, 0, 0}, w, 0x444444);
		i += 32;
	}
}

/*
** **************************************************************************
**	void ft_editor_renderer(t_wolf3d *wolf)
**
**	Function that render all images to window.
** **************************************************************************
*/

void	ft_editor_renderer(t_wolf3d *wolf)
{
	ft_bzero(wolf->sdl->pixels, 4 * WIN_WIDTH * WIN_HEIGHT);
	SDL_SetRenderDrawColor(wolf->sdl->renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(wolf->sdl->renderer);
	ft_editor_draw_line(wolf);
	// ft_editor_draw_map_new_sector_iso(wolf);
	ft_editor_draw_map_2d(wolf, wolf->sector);
	ft_editor_draw_mouse_vertex(wolf);
	if (wolf->sector_status == 1)
	{
		if (!ft_sector_check_sector(wolf))
			ft_editor_sector_draw_line_to_vertex(wolf);
	}
	SDL_UpdateTexture(wolf->sdl->text, 0, wolf->sdl->pixels, WIN_WIDTH * 4);
	SDL_RenderCopy(wolf->sdl->renderer, wolf->sdl->text, NULL, NULL);
	SDL_RenderPresent(wolf->sdl->renderer);
}