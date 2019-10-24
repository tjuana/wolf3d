/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:54:20 by tjuana            #+#    #+#             */
/*   Updated: 2019/10/24 18:58:33 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_load_textures(t_wolf3d *w)
{
	w->weapon_texture = ft_sdl_load_bmp("Textures/pistol.bmp");
	w->sdl->textures[0] = ft_sdl_load_bmp("Textures/bluestone.bmp");
	w->sdl->textures[1] = ft_sdl_load_bmp("Textures/WALL14.bmp");
	w->sdl->textures[2] = ft_sdl_load_bmp("Textures/WALL8.bmp");
	w->sdl->textures[3] = ft_sdl_load_bmp("Textures/WALL12.bmp");
	w->sdl->textures[4] = ft_sdl_load_bmp("Textures/WALL66.bmp");
	w->sdl->textures[5] = ft_sdl_load_bmp("Textures/WALL70.bmp");
	w->sdl->textures[6] = ft_sdl_load_bmp("Textures/WALL78.bmp");
	w->sdl->textures[7] = ft_sdl_load_bmp("Textures/greystone.bmp");
	w->sdl->textures[8] = ft_sdl_load_bmp("Textures/WALL2.bmp");
	w->sdl->textures[9] = ft_sdl_load_bmp("Textures/WALL4.bmp");
	w->sdl->textures[10] = ft_sdl_load_bmp("Textures/Grey9.bmp");
	w->sdl->textures[11] = ft_sdl_load_bmp("Textures/Grey11.bmp");
	w->sdl->textures[12] = ft_sdl_load_bmp("Textures/WALL6.bmp");
	w->sdl->textures[13] = ft_sdl_load_bmp("Textures/WALL52.bmp");
	w->sdl->textures[14] = ft_sdl_load_bmp("Textures/WALL44.bmp");
	w->sdl->textures[15] = ft_sdl_load_bmp("Textures/wood.bmp");
	w->sdl->textures[16] = ft_sdl_load_bmp("Textures/Wood1.bmp");
	w->sdl->textures[17] = ft_sdl_load_bmp("Textures/Wood3.bmp");
	w->sdl->textures[18] = ft_sdl_load_bmp("Textures/WALL90.bmp");
	w->sdl->textures[19] = ft_sdl_load_bmp("Textures/WALL68.bmp");
	w->sdl->textures[20] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[21] = ft_sdl_load_bmp("Textures/pillar.bmp");
	w->sdl->textures[22] = ft_sdl_load_bmp("Textures/barrel.bmp");
}

void		renderer(t_wolf3d *wolf)
{
	//ft_animation_play(wolf);
	ft_bzero(wolf->sdl->text_buf, 4 * WIN_WIDTH * WIN_HEIGHT);
	SDL_SetRenderDrawColor(wolf->sdl->renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(wolf->sdl->renderer);
	//ft_multithreading(wolf);
	//ft_draw_animation(wolf);
	SDL_UpdateTexture(wolf->sdl->text, 0, wolf->sdl->text_buf, WIN_WIDTH * 4);
	SDL_RenderCopy(wolf->sdl->renderer, wolf->sdl->text, NULL, NULL);
	SDL_RenderPresent(wolf->sdl->renderer);
}