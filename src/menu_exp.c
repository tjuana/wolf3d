/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/06 18:59:20 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static void ft_menu_lit(t_wolf3d *w, int id)
**	Function lit part of display
** **************************************************************************
*/

static void	ft_menu_lit(t_wolf3d *w, int id)
{
	SDL_Texture	*tmp_texture;
	SDL_Rect	*tmp_rect;
	int			x;

	tmp_texture = NULL;
	x = ((WIN_W * 0.2 * id) - (WIN_W * 0.15));
	id == 5 ? x = (WIN_W - (WIN_W * 0.15)) : 0;
	if (w->sdl->font.half_menu != id)
	{
		ft_menu(w);
		tmp_rect = ft_create_rect(WIN_W * 0.1, WIN_H * 0.2, x, WIN_H * 0.2);
		tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, w->sdl->font.surf[id]);
		tmp_texture == NULL ? ft_sdl_error(w) : 0;
		SDL_SetTextureBlendMode(tmp_texture, SDL_BLENDMODE_BLEND) != 0 ? ft_sdl_error(w) : 0;
		SDL_RenderCopy(w->sdl->renderer, tmp_texture, NULL, tmp_rect) != 0 ? ft_sdl_error(w) : 0;
		SDL_DestroyTexture(tmp_texture);
		tmp_rect = ft_create_rect(WIN_W * 0.1, WIN_H * 0.2, x, 0);
		tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, w->sdl->font.surf[6]);
		tmp_texture == NULL ? ft_sdl_error(w) : 0;
		SDL_RenderCopy(w->sdl->renderer, tmp_texture, NULL, tmp_rect) != 0 ? ft_sdl_error(w) : 0;
		SDL_DestroyTexture(tmp_texture);
		w->sdl->font.half_menu = id;
	}
	return ;
}

/*
** **************************************************************************
**	static void ft_menu_authors(t_wolf3d *w)
**	Function will show authors when pressed "Authors"
** **************************************************************************
*/

static void	ft_menu_authors(t_wolf3d *w)
{
	SDL_Texture	*tmp_texture;
	int			x;
	int			y;

	w->pl.menu = 5;
	tmp_texture = NULL;
	tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, w->sdl->font.surf[0]);
	tmp_texture == NULL ? ft_sdl_error(w) : 0;
	SDL_SetTextureBlendMode(tmp_texture, SDL_BLENDMODE_NONE) != 0 ? ft_sdl_error(w) : 0;
	SDL_RenderCopy(w->sdl->renderer, tmp_texture, NULL, NULL) != 0 ? ft_sdl_error(w) : 0;
	SDL_DestroyTexture(tmp_texture);
	ft_font_preset(w, 72, 24, 73);
	x = (WIN_W / 2) - (3.5 * w->sdl->font.g_sz);
	y = WIN_H / 2;
	ft_putstr_sdl(w, "nshelly", x, y - (w->sdl->font.f_sz * 2));
	ft_putstr_sdl(w, "dorange-", x, y - w->sdl->font.f_sz);
	ft_putstr_sdl(w, "tjuana", x, y);
	ft_putstr_sdl(w, "drafe", x, y + (w->sdl->font.f_sz));
	TTF_CloseFont(w->sdl->font.ptr);
}

/*
** **************************************************************************
**	static void ft_menu_guide(t_wolf3d *w)
**	Function will show guide when pressed "How to play"
** **************************************************************************
*/

static void	ft_menu_guide(t_wolf3d *w)
{
	SDL_Texture	*tmp_texture;
	int	x;
	int	y;

	w->pl.menu = 3;
	tmp_texture = NULL;
	ft_font_preset(w, 72, 24, 73);
	x = (WIN_W / 2) - (5 * w->sdl->font.g_sz);
	y = WIN_H / 2;
	tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, w->sdl->font.surf[0]);
	tmp_texture == NULL ? ft_sdl_error(w) : 0;
	SDL_SetTextureBlendMode(tmp_texture, SDL_BLENDMODE_NONE) != 0 ? ft_sdl_error(w) : 0;
	SDL_RenderCopy(w->sdl->renderer, tmp_texture, NULL, NULL) != 0 ? ft_sdl_error(w) : 0;
	SDL_DestroyTexture(tmp_texture);
	ft_putstr_sdl(w, "How to play ?", x, 20);
	ft_putstr_sdl(w, "< ESC >       - For pause", x * 0.8, y - (w->sdl->font.f_sz * 3));
	ft_putstr_sdl(w, "< W A S D >   - Movement", x * 0.8, y - (w->sdl->font.f_sz * 2));
	ft_putstr_sdl(w, "< E >           - Interaction", x * 0.8, y - w->sdl->font.f_sz);
	ft_putstr_sdl(w, "< SPACE >      - Jump", x * 0.8, y);
	ft_putstr_sdl(w, "< SHIFT >       - Sprint", x * 0.8, y + w->sdl->font.f_sz);
	ft_putstr_sdl(w, "< Arrow Keys > - camera", x * 0.8, y + (w->sdl->font.f_sz * 2));
	TTF_CloseFont(w->sdl->font.ptr);
}

/*
** **************************************************************************
**	int ft_menu_button(t_wolf3d *w, int x, int click)
**	Function return button number according to mouse x & y
** **************************************************************************
*/

int			ft_menu_button(t_wolf3d *w, int x, int click)
{
	int	button_id;

	button_id = 0;
	if (w->pl.menu == 1)
	{
		((x > 0) && (x < (WIN_W * 0.2))) ? button_id = 1 : 0;
		((x > (WIN_W * 0.2)) && (x < (WIN_W * 0.4))) ? button_id = 2 : 0;
		((x > (WIN_W * 0.4)) && (x < (WIN_W * 0.6))) ? button_id = 3 : 0;
		((x > (WIN_W * 0.6)) && (x < (WIN_W * 0.8))) ? button_id = 4 : 0;
		((x > (WIN_W * 0.8)) && (x < WIN_W)) ? button_id = 5 : 0;
		button_id == 1 && click == 1 ? w->pl.menu = 0 : 0;
		button_id == 2 && click == 1 ? ft_menu_guide(w) : 0;
		button_id == 3 && click == 1 ? button_id = 0 : 0;
		button_id == 4 && click == 1 ? ft_menu_authors(w) : 0;
		button_id == 5 && click == 1 ? w->sdl->running = 0 : 0;
		click == 1 ? 0 : ft_menu_lit(w, button_id);
	}
	return (button_id);
}
