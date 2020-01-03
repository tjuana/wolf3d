/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:26:38 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/03 18:04:32 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		renderer(t_wolf3d *w)
{
	ft_animation_play(w);
	ft_bzero(w->sdl->pixels, 4 * WIN_WIDTH * WIN_HEIGHT);
	//SDL_SetRenderDrawColor(w->sdl->renderer, 0xff, 0xff, 0x61, 0xff);//yellow
	//SDL_RenderClear(w->sdl->renderer);
	if (w->pl.menu == 0)
	{
		threading(w);
		ft_draw_animation(w);
		ft_draw_map(w);
		SDL_RenderClear(w->sdl->renderer);
		SDL_UpdateTexture(w->sdl->text, 0, w->sdl->pixels, WIN_WIDTH * 4);
		SDL_RenderCopy(w->sdl->renderer, w->sdl->text, NULL, NULL);
		ft_font_preset(w, 56, 71, 1);
		ft_putstr_sdl(w, "Life:", w->sdl->font.g_sz * 15, WIN_HEIGHT - w->sdl->font.f_sz * 2.5);
		ft_putstr_sdl(w, ft_itoa(w->pl.st.life), w->sdl->font.g_sz * 20, WIN_HEIGHT - w->sdl->font.f_sz * 2.5);
		ft_putstr_sdl(w, "Ammo:", w->sdl->font.g_sz * 15, WIN_HEIGHT - w->sdl->font.f_sz * 1.5);
		ft_putstr_sdl(w, ft_itoa(w->pl.st.ammo), w->sdl->font.g_sz * 21, WIN_HEIGHT - w->sdl->font.f_sz * 1.5);
		TTF_CloseFont(w->sdl->font.ptr);
	}
	//	ft_menu(w);
	SDL_RenderPresent(w->sdl->renderer);
}
