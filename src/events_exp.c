/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/04 21:43:14 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static void ft_left_right(t_wolf3d *w)
**	Function for move left & right
** **************************************************************************
*/

static void		ft_left_right(t_wolf3d *w)
{
	if (w->arr[13] == 1)
	{
		w->sdl->i = 1;
		ft_load_sound(w);
		if (ft_step_left_check(w, 1))
			w->pl.pos.x += -w->pl.dir.y * (w->ms / 2);
		if (ft_step_left_check(w, 0))
			w->pl.pos.y += w->pl.dir.x * (w->ms / 2);
	}
	if (w->arr[14] == 1)
	{
		w->sdl->i = 1;
		ft_load_sound(w);
		if (ft_step_right_check(w, 1))
			w->pl.pos.x += w->pl.dir.y * (w->ms / 2);
		if (ft_step_right_check(w, 0))
			w->pl.pos.y += -w->pl.dir.x * (w->ms / 2);
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

/*
** **************************************************************************
**	static void ft_use_events_exp(t_wolf3d *w)
**	Second function to use events array
** **************************************************************************
*/

static void		ft_use_events_exp(t_wolf3d *w)
{
	w->arr[2] == 1 ? ft_left_rotation(w) : 0;
	w->arr[3] == 1 ? ft_right_rotation(w) : 0;
	w->arr[10] == 1 ? ft_left_rotation(w) : 0;
	w->arr[11] == 1 ? ft_right_rotation(w) : 0;
	if ((w->arr[4] == 1) && (w->pl.st.ammo > 0 && w->pl.st.ammo < MAX_AMMO))
	{
		w->pl.st.ammo--;
		ft_play_shot(w);
	}
	w->arr[5] == 1 ? ft_play_music(w) : 0;
	w->arr[6] == 1 ? ft_test_mv_p(w) : 0;
	w->arr[7] == 1 ? ft_test_mv_l(w) : 0;
	w->arr[8] == 1 ? w->ms = 0.05 : 0;
	w->arr[8] == 0 || w->arr[1] == 1 || w->arr[13] == 1 || w->arr[14] == 1 \
	? w->ms = 0.03 : 0;
	w->arr[12] == 1 ? ft_door_open(w) : 0;
}

/*
** **************************************************************************
**	void ft_use_events(t_wolf3d *w
**	First function to use events array
** **************************************************************************
*/

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
	ft_left_right(w);
	ft_use_events_exp(w);
}
