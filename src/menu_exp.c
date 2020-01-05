/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/05 17:00:04 by drafe            ###   ########.fr       */
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
	SDL_Texture	*tmp_texture;
	
	tmp_texture = NULL;
	w->sdl->font.surf[0] = IMG_Load("bigfatpng.png");// bigfatpng menu_clear arrow cloud
	w->sdl->font.surf[0] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	w->sdl->font.surf[1] = IMG_Load("play_logo.png");
	w->sdl->font.surf[1] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	w->sdl->font.surf[2] = IMG_Load("how_to_play_logo.png");
	w->sdl->font.surf[2] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	w->sdl->font.surf[3] = IMG_Load("map_editor_logo.png");
	w->sdl->font.surf[3] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	w->sdl->font.surf[4] = IMG_Load("authors_logo.png");
	w->sdl->font.surf[4] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	w->sdl->font.surf[5] = IMG_Load("exit_logo.png");
	w->sdl->font.surf[5] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	w->sdl->font.surf[6] = IMG_Load("cloud.png");
	w->sdl->font.surf[6] == NULL ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, w->sdl->font.surf[0]);
	tmp_texture == NULL ? ft_sdl_error(w) : 0;
	SDL_SetTextureBlendMode(tmp_texture, SDL_BLENDMODE_NONE) != 0 ? ft_sdl_error(w) : 0;
	SDL_RenderCopy(w->sdl->renderer, tmp_texture, NULL, NULL) != 0 ? ft_sdl_error(w) : 0;
	SDL_DestroyTexture(tmp_texture);
	ft_menu(w);
}

/*
** **************************************************************************
**	void ft_menu_back(t_wolf3d *w)
**	Function to draw sub_menu
** **************************************************************************
*/

void ft_menu_play(t_wolf3d *w)
{
	w->pl.menu = 0;
}
