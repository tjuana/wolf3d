/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/18 22:39:50 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	int ft_mouse_mv(SDL_Event *e, t_moves *m, t_w *w)
**	Function to handle mouse move
** **************************************************************************
*/

int				ft_mouse_mv(SDL_Event *e, t_wolf3d *w)
{
	double	old_dir_x;
	double	old_pl_x;
	double	mou_x;
	double	sign;

	old_dir_x = w->pl.dir.x;
	old_pl_x = w->pl.plane.x;
	mou_x = e->motion.xrel;
	mou_x = mou_x / WIN_HEIGHT;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	//if (SDL_SetRelativeMouseMode(SDL_TRUE) != 0)
	//	ft_sdl_error();
	sign = -0.2 * 0.1;//w->r_speed = 0.1;
	if (mou_x < 0)
		sign = 0.2 * 0.1;//w->r_speed = 0.1;
	w->pl.dir.x = w->pl.dir.x * cos(sign) - w->pl.dir.y * sin(sign);
	w->pl.dir.y = old_dir_x * sin(sign) + w->pl.dir.y * cos(sign);
	w->pl.plane.x = w->pl.plane.x * cos(sign) - w->pl.plane.y * sin(sign);
	w->pl.plane.y = old_pl_x * sin(sign) + w->pl.plane.y * cos(sign);
	//printf("%i %i sign=%f   w->r_speed=%f\n", e->motion.xrel, e->motion.yrel, sign, w->r_speed);
	return (1);
}