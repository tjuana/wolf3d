/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:40:14 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/10 20:48:40 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
	SDL_Color			color = {85, 25, 20, 0};
	//SDL_Color			bgcolor = {0, 0, 0, 0};
	SDL_Surface			*text_surf;
	SDL_Texture			*tmp_texture;
	SDL_Rect			a;
	
	if ((x < 0) || (y < 0) || (str == NULL) || (x > WIN_WIDTH) || (y > WIN_HEIGHT))
		return ;
	tmp_texture = NULL;
	if (TTF_Init() == -1)
		ft_sdl_error(w);
	if (!(w->sdl->font = TTF_OpenFont("fonts/procyon_si.ttf", w->pl.st.font_sz)))
		ft_sdl_error(w);
	if (TTF_SizeText(w->sdl->font, str, &a.w, &a.h) == -1)
		ft_sdl_error(w);
	//a = ft_create_rect(a.w, a.h, (WIN_WIDTH - a.w) / 2 , (WIN_HEIGHT - a.h) / 2);
	a = ft_create_rect(a.w, a.h, x, y);
	if (!(text_surf = TTF_RenderText_Blended(w->sdl->font, str, color)))
		ft_sdl_error(w);
	else
	{
		tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, text_surf);
		if (!tmp_texture)
			ft_sdl_error(w);
		//if (SDL_BlitSurface(text_surface, NULL, w->pl.st.jet_surf, NULL) == -1)
		//	ft_sdl_error(w);
		//perhaps we can reuse it, but I assume not for simplicity.
		SDL_FreeSurface(text_surf);
	}
	if (SDL_RenderCopy(w->sdl->renderer, tmp_texture, 0, &a) == -1)
		ft_sdl_error(w);
	SDL_DestroyTexture(tmp_texture);
	//SDL_RenderPresent(w->sdl->renderer);
	TTF_CloseFont(w->sdl->font);
	w->sdl->font = NULL;
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