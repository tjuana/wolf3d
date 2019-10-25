/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:26:38 by tjuana            #+#    #+#             */
/*   Updated: 2019/10/25 14:39:14 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		renderer(t_wolf3d *wolf)
{
	//ft_animation_play(wolf);
	ft_bzero(wolf->sdl->text_buf, 4 * WIN_WIDTH * WIN_HEIGHT);
	SDL_SetRenderDrawColor(wolf->sdl->renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(wolf->sdl->renderer);
	threading(wolf);
	//ft_draw_animation(wolf);
	SDL_UpdateTexture(wolf->sdl->text, 0, wolf->sdl->text_buf, WIN_WIDTH * 4);
	SDL_RenderCopy(wolf->sdl->renderer, wolf->sdl->text, NULL, NULL);
	SDL_RenderPresent(wolf->sdl->renderer);
}