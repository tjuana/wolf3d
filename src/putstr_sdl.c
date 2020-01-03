/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:40:14 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/03 18:24:07 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	SDL_Rect ft_create_rect(int w, int h, int x, int y)
**	Function to set font colot and size
** **************************************************************************
*/

int			ft_font_preset(t_wolf3d *w, int b, int g, int r)
{
	(b > 72) || (b < 1) ? b = 72 : 0;
	(r > 72) || (r < 1) ? r = 72 : 0;
	(g > 72) || (g < 1) ? r = 72 : 0;
	w->sdl->font.color.a = 0;
	w->sdl->font.color.b = b;
	w->sdl->font.color.g = g;
	w->sdl->font.color.r = r;
	w->sdl->font.f_sz = b;
	if (!(w->sdl->font.ptr = TTF_OpenFont(FONT_PATH, w->sdl->font.f_sz)))
		ft_sdl_error(w);
	if (TTF_GlyphMetrics(w->sdl->font.ptr, 'A', 0, 0, 0, 0, &w->sdl->font.g_sz) == -1)
		ft_sdl_error(w);
	return (0);
}

/*
** **************************************************************************
**	SDL_Rect ft_create_rect(int w, int h, int x, int y)
**	Function to create SDL_Rect
** **************************************************************************
*/

SDL_Rect	ft_create_rect(int w, int h, int x, int y)
{
	SDL_Rect	tmp;

	tmp.h = h;
	tmp.w = w;
	tmp.x = x;
	tmp.y = y;
	return (tmp);
}

/*
** **************************************************************************
**	void ft_pl_stats(t_wolf3d *w)
**	Function to print words
** **************************************************************************
*/

void			ft_putstr_sdl(t_wolf3d *w, char *str, int x, int y)
{
	SDL_Surface	*text_surf;
	SDL_Texture	*tmp_texture;
	SDL_Rect	a;

	if ((x < 0) || (y < 0) || (str == NULL) || (x > WIN_WIDTH) || (y > WIN_HEIGHT))
		return ;
	tmp_texture = NULL;
	if (TTF_SizeText(w->sdl->font.ptr, str, &w->sdl->font.w, &w->sdl->font.h) == -1)
		ft_sdl_error(w);
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
	if (SDL_RenderCopy(w->sdl->renderer, tmp_texture, 0, &a) != 0)
		ft_sdl_error(w);
	SDL_DestroyTexture(tmp_texture);
}

/*	
	procyon_si.ttf
	DooMLeft.ttf
	DooMLeft2.ttf
	DooMLeftOutline.ttf
	DooMRight.ttf
	DooMRight2.ttf
	DooMRightOutline.ttf

printf("The font max height is: %d\n", TTF_FontHeight(w->sdl->font));
	//solid//shaded + SDL_Color bgcolor = {0xff, 0xff, 0xff, 0};
	
	SDL_version			compile_version;
	const SDL_version	*link_version;
	
	link_version = TTF_Linked_Version();
	SDL_TTF_VERSION(&compile_version);
	printf("\nCompiled with SDL_ttf version: %d.%d.%d\n", 
		compile_version.major, compile_version.minor, compile_version.patch);
	printf("Running with SDL_ttf version: %d.%d.%d\n", 
		link_version->major, link_version->minor, link_version->patch);
*/