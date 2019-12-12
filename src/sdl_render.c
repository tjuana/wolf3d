/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:26:38 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/11 16:01:54 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		renderer(t_wolf3d *w)
{
	ft_animation_play(w);
	ft_bzero(w->sdl->pixels, 4 * WIN_WIDTH * WIN_HEIGHT);
	SDL_SetRenderDrawColor(w->sdl->renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(w->sdl->renderer);
	threading(w);
	ft_draw_animation(w);
	ft_draw_map(w);
	SDL_UpdateTexture(w->sdl->text, 0, w->sdl->pixels, WIN_WIDTH * 4);
	SDL_RenderCopy(w->sdl->renderer, w->sdl->text, NULL, NULL);
	w->pl.st.font_sz = 56;
	ft_putstr_sdl(w, "life:", w->pl.st.font_sz * 5, WIN_HEIGHT - 66);
	ft_putstr_sdl(w, ft_itoa(w->pl.st.life), w->pl.st.font_sz * 7, WIN_HEIGHT - 66);
	ft_putstr_sdl(w, "ammo:", w->pl.st.font_sz * 9, WIN_HEIGHT - 66);
	ft_putstr_sdl(w, ft_itoa(w->pl.st.ammo), w->pl.st.font_sz * 12, WIN_HEIGHT - 66);
	SDL_RenderPresent(w->sdl->renderer);
}
