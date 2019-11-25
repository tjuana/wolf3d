/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/25 21:22:22 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static void ft_keydown(t_wolf3d *w, SDL_Event e)
**	Function to handle SDL KEYDOWN
** **************************************************************************
*/

static void		ft_keydown(t_wolf3d *w, SDL_Event e)
{
	e.key.keysym.scancode == SDL_SCANCODE_ESCAPE ?
	w->sdl->running = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_W ? w->arr[0] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_UP ? w->arr[0] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_S ? w->arr[1] = 1 : 0;	
	e.key.keysym.scancode == SDL_SCANCODE_DOWN ? w->arr[1] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_A ? w->arr[2] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_LEFT ? w->arr[10] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_D ? w->arr[3] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_RIGHT ? w->arr[11] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_Q ? w->arr[5] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_P ? w->arr[6] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_L ? w->arr[7] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_LSHIFT ? w->arr[8] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_RSHIFT ? w->arr[9] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_SPACE ? w->arr[12] = 1 : 0;
}

/*
** **************************************************************************
**	static void ft_keyup(t_wolf3d *w, SDL_Event e)
**	Function to handle SDL KEYUP
** **************************************************************************
*/

static void		ft_keyup(t_wolf3d *w, SDL_Event e)
{
	e.key.keysym.scancode == SDL_SCANCODE_W ? w->arr[0] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_UP ? w->arr[0] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_S ? w->arr[1] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_DOWN ? w->arr[1] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_A ? w->arr[2] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_LEFT ? w->arr[10] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_D ? w->arr[3] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_RIGHT ? w->arr[11] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_Q ? w->arr[5] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_P ? w->arr[6] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_L ? w->arr[7] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_LSHIFT ? w->arr[8] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_RSHIFT ? w->arr[9] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_SPACE ? w->arr[12] = 0 : 0;
}

/*
** **************************************************************************
**	void ft_handle_events(t_wolf3d *w)
**	Function to init doors state
** **************************************************************************
*/

void			ft_handle_events(t_wolf3d *w)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		e.type == SDL_QUIT ? w->sdl->running = 0 : 0;
		if (e.type == SDL_KEYDOWN)
			ft_keydown(w, e);
		if (e.type == SDL_KEYUP)
			ft_keyup(w, e);
		if (e.type == SDL_MOUSEMOTION)
			ft_mouse_mv(&e, w);
		if (e.button.type == SDL_MOUSEBUTTONDOWN)
			e.button.button == 1 ? w->arr[4] = 1 : 0;
		if (e.button.type == SDL_MOUSEBUTTONUP)
			e.button.button == 1 ? w->arr[4] = 0 : 0;
	}
}
