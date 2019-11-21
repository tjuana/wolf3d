/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/21 14:46:27 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_handle_events(t_wolf3d *w)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		e.type == SDL_QUIT ? w->sdl->running = 0 : 0;
		if (e.type == SDL_KEYDOWN)
		{
			e.key.keysym.scancode == SDL_SCANCODE_ESCAPE ?
			w->sdl->running = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_W ? w->arr[0] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_S ? w->arr[1] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_A ? w->arr[2] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_D ? w->arr[3] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_SPACE ? w->arr[4] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_Q ? w->arr[5] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_P ? w->arr[6] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_L ? w->arr[7] = 1 : 0;
		}
		if (e.type == SDL_KEYUP)
		{
			e.key.keysym.scancode == SDL_SCANCODE_W ? w->arr[0] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_S ? w->arr[1] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_A ? w->arr[2] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_D ? w->arr[3] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_SPACE ? w->arr[4] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_Q ? w->arr[5] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_P ? w->arr[6] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_L ? w->arr[7] = 0 : 0;
		}
		if (e.type == SDL_MOUSEMOTION)
			ft_mouse_mv(&e, w);
		if (e.button.type == SDL_MOUSEBUTTONDOWN)
			e.button.button == 1 ? w->arr[4] = 1 : 0;
		if (e.button.type == SDL_MOUSEBUTTONUP)
			e.button.button == 1 ? w->arr[4] = 0 : 0;
	}
}

static void		ft_left_rotation(t_wolf3d *w)
{
	w->pl.old_dirX = w->pl.dir.x;
	w->pl.dir.x = w->pl.dir.x * w->c.crs - w->pl.dir.y * w->c.srs;
	w->pl.dir.y = w->pl.old_dirX * w->c.srs + w->pl.dir.y * w->c.crs;
	w->pl.old_planeX = w->pl.plane.x;
	w->pl.plane.x = w->pl.plane.x * w->c.crs - w->pl.plane.y * w->c.srs;
	w->pl.plane.y = w->pl.old_planeX * w->c.srs + w->pl.plane.y * w->c.crs;
}

static void		ft_right_rotation(t_wolf3d *w)
{
	w->pl.old_dirX = w->pl.dir.x;
	w->pl.dir.x = w->pl.dir.x * w->c.mcrs - w->pl.dir.y * w->c.msrs;
	w->pl.dir.y = w->pl.old_dirX * w->c.msrs + w->pl.dir.y * w->c.mcrs;
	w->pl.old_planeX = w->pl.plane.x;
	w->pl.plane.x = w->pl.plane.x * w->c.mcrs - w->pl.plane.y * w->c.msrs;
	w->pl.plane.y = w->pl.old_planeX * w->c.msrs + w->pl.plane.y * w->c.mcrs;
}

void			ft_use_events(t_wolf3d *w)
{
	if (w->arr[0] == 1)
	{
		w->sdl->i = 1;
		ft_load_sound(w);
		if (ft_step_forward_check(w, 1))
			w->pl.pos.x += w->pl.dir.x * w->ms;
		if (ft_step_forward_check(w, 0))
			w->pl.pos.y += w->pl.dir.y * w->ms;
	}
	if (w->arr[1] == 1)
	{
		if (ft_step_back_check(w, 1))
			w->pl.pos.x -= w->pl.dir.x * w->ms;
		if (ft_step_back_check(w, 0))
			w->pl.pos.y -= w->pl.dir.y * w->ms;
	}
	w->arr[2] == 1 ? ft_left_rotation(w) : 0;
	w->arr[3] == 1 ? ft_right_rotation(w) : 0;
	w->arr[4] == 1 ? ft_play_shot(w) : 0;
	w->arr[5] == 1 ? ft_play_music(w) : 0;
	w->arr[6] == 1 ? ft_test_mv_p(w) : 0;
	w->arr[7] == 1 ? ft_test_mv_l(w) : 0;
}
