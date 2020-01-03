/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/03 20:55:51 by drafe            ###   ########.fr       */
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
		SDL_SetTextureBlendMode(tmp_texture, SDL_BLENDMODE_BLEND) != 0 ? ft_sdl_error(w) : 0;
		SDL_RenderCopy(w->sdl->renderer, tmp_texture, NULL, &tmp_rect) != 0 ? ft_sdl_error(w) : 0;
		SDL_DestroyTexture(tmp_texture);
		//w->sdl->font.half_menu = 1;
		w->sdl->font.half_menu = id;
	}
	return ;
}
	
/*

tmp_rect = ft_create_rect(WIN_WIDTH * 0.2, WIN_HEIGHT, x - (WIN_WIDTH * 0.2), 0);
		
		if (!(tmp_surf = SDL_CreateRGBSurface(0, WIN_WIDTH * 0.2, WIN_HEIGHT, 8, 0, 0, 0, 0)))
			ft_sdl_error(w);
		SDL_SetRenderDrawColor(w->sdl->renderer, 0x00, 0xFF, 0xFF, 0x59);
		SDL_RenderDrawRect(w->sdl->renderer, &tmp_rect);
			//if ((SDL_FillRect(tmp_surf, &tmp_rect, 9434934)) != 0)
			//	ft_sdl_error(w);	
		tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, tmp_surf);
		if (!tmp_texture)
			ft_sdl_error(w);
		
		if (SDL_RenderCopy(w->sdl->renderer, tmp_texture, 0, &tmp_rect) == -1)
			ft_sdl_error(w);
		SDL_FreeSurface(tmp_surf);
		SDL_DestroyTexture(tmp_texture);

//if (SDL_SetRenderDrawBlendMode(w->sdl->renderer, SDL_BLENDMODE_ADD) != 0)
		//	ft_sdl_error(w);
		//if ((SDL_FillRect(tmp_surf, &tmp_rect, 99)) != 0)
		//SDL_BlitSurface(SDL_Surface *src, const SDL_Rect *srcrect, SDL_Surface*dst, SDL_Rect *dstrect)
		//if ((SDL_BlitSurface(tmp_surf, &tmp_rect, tmp_surf, NULL)) != 0)
		//SDL_CreateRGBSurface(0, width, height, 32,rmask, gmask, bmask, amask);
tmp_texture = NULL;
a = ft_create_rect(w->sdl->font.w, w->sdl->font.h, x, y);

	if (!(text_surf = TTF_RenderText_Blended(w->sdl->font.ptr, str, w->sdl->font.color)))
		ft_sdl_error(w);
	else
	{
		tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, text_surf);
		if (!tmp_texture)
			ft_sdl_error(w);
		SDL_FreeSurface(text_surf);
	}
	if (SDL_RenderCopy(w->sdl->renderer, tmp_texture, 0, &a) == -1)
		ft_sdl_error(w);
	SDL_DestroyTexture(tmp_texture);

*/

/*
** **************************************************************************
**	static void ft_show_authors(t_wolf3d *w)
**	Function will show authors when pressed "How to play"
** **************************************************************************
*/

static void	ft_menu_authors(t_wolf3d *w)
{
	int			x;
	int			y;


	ft_font_preset(w, 72, 24, 73);
	x = (WIN_WIDTH / 2) - (5.5 * w->sdl->font.g_sz);
	y = WIN_HEIGHT / 2;
	ft_putstr_sdl(w, "nshelly", x, y - (w->sdl->font.f_sz * 2));
	ft_putstr_sdl(w, "dorange-", x, y - w->sdl->font.f_sz);
	ft_putstr_sdl(w, "tjuana", x, y);
	ft_putstr_sdl(w, "drafe", x, y + (w->sdl->font.f_sz));
	TTF_CloseFont(w->sdl->font.ptr);
	
}

/*
** **************************************************************************
**	static void ft_show_authors(t_wolf3d *w)
**	Function will show guide when pressed "How to play"
** **************************************************************************
*/

static void	ft_menu_guide(t_wolf3d *w)
{
	int	x;
	int	y;

	ft_font_preset(w, 72, 24, 73);
	x = (WIN_WIDTH / 2) - (5.5 * w->sdl->font.g_sz);
	y = WIN_HEIGHT / 2;
	ft_putstr_sdl(w, "How to play ?", x, 20);
	ft_putstr_sdl(w, "< ESC > for pause.", x, y - (w->sdl->font.f_sz * 3));
	ft_putstr_sdl(w, "< W A S D > Movement", x, y - (w->sdl->font.f_sz * 2));
	ft_putstr_sdl(w, " < E > interaction", x, y - w->sdl->font.f_sz);
	ft_putstr_sdl(w, "< SPACE > jump", x, y);
	ft_putstr_sdl(w, "< SHIFT > sprint", x, y + w->sdl->font.f_sz);
	ft_putstr_sdl(w, "< Arrow Keys >", x, y + (w->sdl->font.f_sz * 2));
	ft_putstr_sdl(w, "Exit", x, y + (w->sdl->font.f_sz * 3));
	TTF_CloseFont(w->sdl->font.ptr);
}

/*
** **************************************************************************
**	int ft_menu_button(t_wolf3d *w, int x, int button_id)
**	Function return button number according to mouse x & y
** **************************************************************************
*/

int			ft_menu_button(t_wolf3d *w, int x, int click)
{
	int	button_id;

	button_id = 0;
	((x > 0) && (x < (WIN_WIDTH * 0.2))) ? button_id = 1 : 0;
	((x > (WIN_WIDTH * 0.2)) && (x < (WIN_WIDTH * 0.4))) ? button_id = 2 : 0;
	((x > (WIN_WIDTH * 0.4)) && (x < (WIN_WIDTH * 0.6))) ? button_id = 3 : 0;
	((x > (WIN_WIDTH * 0.6)) && (x < (WIN_WIDTH * 0.8))) ? button_id = 4 : 0;
	((x > (WIN_WIDTH * 0.8)) && (x < WIN_WIDTH)) ? button_id = 5 : 0;
	button_id == 1 && click == 1 ? button_id = 0 : 0;
	button_id == 2 && click == 1 ? ft_menu_guide(w) : 0;
	button_id == 3 && click == 1 ? button_id = 0 : 0;
	button_id == 4 && click == 1 ? ft_menu_authors(w) : 0;
	button_id == 5 && click == 1 ? button_id = 0 : 0;
	ft_menu_lit(w, button_id);
	return (button_id);
	
	
}

/*
** **************************************************************************
**	void ft_menu(t_wolf3d *w)
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
