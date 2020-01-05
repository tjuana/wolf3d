/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/05 17:08:50 by drafe            ###   ########.fr       */
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
	SDL_Rect	tmp_rect;
	int			x;

	x = 0;
	tmp_rect.h = 0;
	tmp_texture = NULL;
	id == 1 ? x = WIN_WIDTH * 0.2 : 0;
	id == 2 ? x = WIN_WIDTH * 0.4 : 0;
	id == 3 ? x = WIN_WIDTH * 0.6 : 0;
	id == 4 ? x = WIN_WIDTH * 0.8 : 0;
	id == 5 ? x = WIN_WIDTH : 0;
	if (w->sdl->font.half_menu != id)
	{
		SDL_RenderClear(w->sdl->renderer);
		tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, w->sdl->font.surf[0]);
		tmp_texture == NULL ? ft_sdl_error(w) : 0;
		SDL_SetTextureBlendMode(tmp_texture, SDL_BLENDMODE_NONE) != 0 ? ft_sdl_error(w) : 0;
		SDL_RenderCopy(w->sdl->renderer, tmp_texture, NULL, NULL) != 0 ? ft_sdl_error(w) : 0;
		SDL_DestroyTexture(tmp_texture);
		ft_menu(w);
		tmp_rect = ft_create_rect(WIN_WIDTH * 0.1, WIN_HEIGHT * 0.2, x - (WIN_WIDTH * 0.15), WIN_HEIGHT * 0.2);
		tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, w->sdl->font.surf[id]);
		tmp_texture == NULL ? ft_sdl_error(w) : 0;
		SDL_SetTextureBlendMode(tmp_texture, SDL_BLENDMODE_BLEND) != 0 ? ft_sdl_error(w) : 0;
		SDL_RenderCopy(w->sdl->renderer, tmp_texture, NULL, &tmp_rect) != 0 ? ft_sdl_error(w) : 0;
		SDL_DestroyTexture(tmp_texture);
		tmp_rect = ft_create_rect(WIN_WIDTH * 0.1, WIN_HEIGHT * 0.2, x - (WIN_WIDTH * 0.15), 0);
		tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, w->sdl->font.surf[6]);
		tmp_texture == NULL ? ft_sdl_error(w) : 0;
		SDL_RenderCopy(w->sdl->renderer, tmp_texture, NULL, &tmp_rect) != 0 ? ft_sdl_error(w) : 0;
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

	printf("SHOW AUTHORS\n");
	w->pl.menu = 5;
	tmp_texture = NULL;
	tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, w->sdl->font.surf[0]);
	tmp_texture == NULL ? ft_sdl_error(w) : 0;
	SDL_SetTextureBlendMode(tmp_texture, SDL_BLENDMODE_NONE) != 0 ? ft_sdl_error(w) : 0;
	SDL_RenderCopy(w->sdl->renderer, tmp_texture, NULL, NULL) != 0 ? ft_sdl_error(w) : 0;
	SDL_DestroyTexture(tmp_texture);
	ft_font_preset(w, 72, 24, 73);
	x = (WIN_WIDTH / 2) - (3.5 * w->sdl->font.g_sz);
	y = WIN_HEIGHT / 2;
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

	w->pl.menu = 5;
	printf("SHOW GUIDE\n");
	tmp_texture = NULL;
	ft_font_preset(w, 72, 24, 73);
	x = (WIN_WIDTH / 2) - (5 * w->sdl->font.g_sz);
	y = WIN_HEIGHT / 2;
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
	//ft_putstr_sdl(w, "Exit", x * 1.1, WIN_HEIGHT - 80);
	TTF_CloseFont(w->sdl->font.ptr);
	w->pl.menu = 3;
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
		((x > 0) && (x < (WIN_WIDTH * 0.2))) ? button_id = 1 : 0;
		((x > (WIN_WIDTH * 0.2)) && (x < (WIN_WIDTH * 0.4))) ? button_id = 2 : 0;
		((x > (WIN_WIDTH * 0.4)) && (x < (WIN_WIDTH * 0.6))) ? button_id = 3 : 0;
		((x > (WIN_WIDTH * 0.6)) && (x < (WIN_WIDTH * 0.8))) ? button_id = 4 : 0;
		((x > (WIN_WIDTH * 0.8)) && (x < WIN_WIDTH)) ? button_id = 5 : 0;
		button_id == 1 && click == 1 ? ft_menu_play(w) : 0;
		button_id == 2 && click == 1 ? ft_menu_guide(w) : 0;
		button_id == 3 && click == 1 ? button_id = 0 : 0;
		button_id == 4 && click == 1 ? ft_menu_authors(w) : 0;
		button_id == 5 && click == 1 ? w->sdl->running = 0 : 0;
		click == 1 ? 0 : ft_menu_lit(w, button_id);
	}
	return (button_id);
}

/*
** **************************************************************************
**	static void ft_menu(t_wolf3d *w)
**	Function will show user our menu
**	(Play, How to play, Map editor, Authors, Exit)
** **************************************************************************
*/

void		ft_menu(t_wolf3d *w)
{
	int	menu_x;
	int	menu_y;
	int	tmp;

	tmp = 0;
	ft_font_preset(w, 72, 24, 73);
	menu_x = (WIN_WIDTH * 0.5) - (5 * w->sdl->font.g_sz);
	menu_y = WIN_HEIGHT * 0.6;
	ft_putstr_sdl(w, "Play", menu_x * 0.15, menu_y);
	ft_putstr_sdl(w, "How to play", menu_x * 0.5, menu_y);
	ft_putstr_sdl(w, "Map editor", menu_x * 1.05, menu_y);
	ft_putstr_sdl(w, "Authors", menu_x * 1.6, menu_y);
	ft_putstr_sdl(w, "Exit", menu_x * 2.15, menu_y);
	TTF_CloseFont(w->sdl->font.ptr);
	return ;
}