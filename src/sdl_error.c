/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/12 19:37:13 by tjuana           ###   ########.fr       */
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
	SDL_Quit();
	exit(-1);
}

int		ft_sdl_init_error(t_sdl *sdl)
{
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, \
	"Couldn't create window and renderer: %s", SDL_GetError());
	if (sdl->wav_buff)
		free(sdl->wav_buff);
	if (sdl->wav_spect)
		free(sdl->wav_spect);	
	
	// free(sdl->wav_len);
	// free(w->sdl->audio_device);
	// free(sdl->surfaces);
	// free(sdl->pixels);
	if (sdl->text)
		SDL_DestroyTexture(sdl->text);
	if (sdl->renderer)
		SDL_DestroyRenderer(sdl->renderer);
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
	IMG_Quit();
	SDL_Quit();
	exit(-1);
}