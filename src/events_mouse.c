/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/18 15:48:05 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	int ft_mouse_mv(SDL_Event *e, t_moves *m, t_w *w)
**	Function to handle mouse move
** **************************************************************************
*/

void	ft_mouse_mv(SDL_Event *e, t_wolf3d *w)
{
	double	old_dir_x;
	double	old_pl_x;
	double	mou_x;
	double	mou_y;
	double	sign;

	old_dir_x = w->pl.dir.x;
	old_pl_x = w->pl.plane.x;
	mou_x = e->motion.xrel;
	mou_y = e->motion.yrel;
	mou_x = mou_x / WIN_HEIGHT;
	mou_y = mou_y / WIN_HEIGHT;
	if (SDL_SetRelativeMouseMode(SDL_TRUE) != 0)
		ft_sdl_error(w);
	sign = -w->rs;
	if (mou_x < 0)
		sign = w->rs;
	sign -= e->motion.xrel / WIN_WIDTH;
	w->pl.dir.x = w->pl.dir.x * cos(sign) - w->pl.dir.y * sin(sign);
	w->pl.dir.y = old_dir_x * sin(sign) + w->pl.dir.y * cos(sign);
	w->pl.plane.x = w->pl.plane.x * cos(sign) - w->pl.plane.y * sin(sign);
	w->pl.plane.y = old_pl_x * sin(sign) + w->pl.plane.y * cos(sign);
}

/*
** **************************************************************************
**	void ft_test_mv_p(t_wolf3d *w) | debug
**	Function to handle P button
** **************************************************************************
*/

void	ft_test_mv_p(t_wolf3d *w)
{
	w->mouse_offset += 15;//camera up
	renderer(w);
		//ft_pl_stats(w);
	printf("P pressed\n");
}

void	ft_test_mv_l(t_wolf3d *w)
{
	w->mouse_offset -= 15;//camera down
	//ft_pl_stats(w);
	printf("P pressed\n");
}