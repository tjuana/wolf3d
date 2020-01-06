/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/06 19:20:58 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	void ft_menu_back(t_wolf3d *w)
**	Function to load and draw background
** **************************************************************************
*/

void ft_menu_back(t_wolf3d *w)
{
	w->sdl->font.surf[0] = IMG_Load("menu/bigfatpng.png");// bigfatpng menu_clear arrow cloud
	w->sdl->font.surf[0] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	w->sdl->font.surf[1] = IMG_Load("menu/play_logo.png");
	w->sdl->font.surf[1] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	w->sdl->font.surf[2] = IMG_Load("menu/how_to_play_logo.png");
	w->sdl->font.surf[2] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	w->sdl->font.surf[3] = IMG_Load("menu/map_editor_logo.png");
	w->sdl->font.surf[3] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	w->sdl->font.surf[4] = IMG_Load("menu/authors_logo.png");
	w->sdl->font.surf[4] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	w->sdl->font.surf[5] = IMG_Load("menu/exit_logo.png");
	w->sdl->font.surf[5] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	w->sdl->font.surf[6] = IMG_Load("menu/cloud.png");
	w->sdl->font.surf[6] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	ft_menu(w);
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
	SDL_Texture	*tmp_texture;
	int	menu_x;
	int	menu_y;
	int	tmp;

	w->pl.menu = 1;
	tmp = 0;
	tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, w->sdl->font.surf[0]);
	tmp_texture == NULL ? ft_sdl_error(w) : 0;
	SDL_SetTextureBlendMode(tmp_texture, SDL_BLENDMODE_NONE) != 0 ? ft_sdl_error(w) : 0;
	SDL_RenderCopy(w->sdl->renderer, tmp_texture, NULL, NULL) != 0 ? ft_sdl_error(w) : 0;
	SDL_DestroyTexture(tmp_texture);
	ft_font_preset(w, 72, 24, 73);
	menu_x = (WIN_W * 0.5) - (5 * w->sdl->font.g_sz);
	menu_y = WIN_H * 0.6;
	ft_putstr_sdl(w, "Play", menu_x * 0.15, menu_y);
	ft_putstr_sdl(w, "How to play", menu_x * 0.5, menu_y);
	ft_putstr_sdl(w, "Map editor", menu_x * 1.05, menu_y);
	ft_putstr_sdl(w, "Authors", menu_x * 1.6, menu_y);
	ft_putstr_sdl(w, "Exit", menu_x * 2.15, menu_y);
	TTF_CloseFont(w->sdl->font.ptr);
	return ;
}