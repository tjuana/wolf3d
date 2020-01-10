/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:34:19 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/10 17:12:13 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_editor_draw_line(t_wolf3d *w)
{
	ft_draw_compass_static(w);
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
	ft_draw_map_new_sector_iso(wolf);
	SDL_UpdateTexture(wolf->sdl->text, 0, wolf->sdl->pixels, WIN_WIDTH * 4);
	SDL_RenderCopy(wolf->sdl->renderer, wolf->sdl->text, NULL, NULL);
	SDL_RenderPresent(wolf->sdl->renderer);
}