/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/03 20:49:18 by drafe            ###   ########.fr       */
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
	e.key.keysym.scancode == SDL_SCANCODE_S ? w->arr[1] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_A ? w->arr[13] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_LEFT ? w->arr[10] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_D ? w->arr[14] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_RIGHT ? w->arr[11] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_Q ? w->arr[5] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_P ? w->arr[6] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_L ? w->arr[7] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_LSHIFT ? w->arr[8] = 1 : 0;
	//e.key.keysym.scancode == SDL_SCANCODE_RSHIFT ? w->arr[9] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_SPACE ? w->arr[12] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_KP_2 ? w->arr[15] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_KP_4 ? w->arr[16] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_KP_6 ? w->arr[17] = 1 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_KP_8 ? w->arr[18] = 1 : 0;
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
	e.key.keysym.scancode == SDL_SCANCODE_S ? w->arr[1] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_A ? w->arr[13] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_LEFT ? w->arr[10] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_D ? w->arr[14] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_RIGHT ? w->arr[11] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_Q ? w->arr[5] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_P ? w->arr[6] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_L ? w->arr[7] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_LSHIFT ? w->arr[8] = 0 : 0;
	//e.key.keysym.scancode == SDL_SCANCODE_RSHIFT ? w->arr[9] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_SPACE ? w->arr[12] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_KP_2 ? w->arr[15] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_KP_4 ? w->arr[16] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_KP_6 ? w->arr[17] = 0 : 0;
	e.key.keysym.scancode == SDL_SCANCODE_KP_8 ? w->arr[18] = 0 : 0;
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
		if ((e.button.type == SDL_MOUSEBUTTONDOWN) && (w->pl.menu == 0))
			e.button.button == 1 ? w->arr[4] = 1 : 0;
		if ((e.button.type == SDL_MOUSEBUTTONUP) && (w->pl.menu == 0))
			e.button.button == 1 ? w->arr[4] = 0 : 0;
		if (e.type == SDL_MOUSEMOTION)
			ft_mouse_mv(w, e);
		ft_menu_button(w, e.motion.x, 0);
	}
}
