/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/19 17:38:45 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	void ft_sdl_error(t_wolf3d *w)
**	Function to print error message and exit
** **************************************************************************
*/

void		ft_sdl_error(t_wolf3d *w)
{
	const char	*out;

	out = SDL_GetError();
	ft_putstr_fd("SDL_Error:", 2);
	ft_putstr_fd(out, 2);
	ft_putstr_fd("\n", 2);
	if (w->sdl->text)
		SDL_DestroyTexture(w->sdl->text);
	if (w->sdl->renderer)
		SDL_DestroyRenderer(w->sdl->renderer);
	if (w->sdl->win)
		SDL_DestroyWindow(w->sdl->win);
	//if (w->surf)
	//	SDL_FreeSurface(w->sdl->surf);
	SDL_Quit();
	exit(-1);
}