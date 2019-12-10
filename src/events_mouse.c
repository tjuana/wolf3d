/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/10 20:47:10 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	void ft_mouse_mv(t_wolf3d *w, SDL_Event e)
**	Function to handle mouse move
** **************************************************************************
*/

void	ft_mouse_mv(t_wolf3d *w, SDL_Event e)
{
	double	old_dir_x;
	double	old_pl_x;
	double	mou_x;
	double	sign;

	old_dir_x = w->pl.dir.x;
	old_pl_x = w->pl.plane.x;
	mou_x = e.motion.xrel;
	mou_x /= WIN_HEIGHT;
	if (SDL_SetRelativeMouseMode(SDL_TRUE) != 0)
		ft_sdl_error(w);
	//w->mouse_offset -= e->motion.yrel;
	sign = -w->rs;
	if (mou_x < 0)
		sign = w->rs;
	sign -= e.motion.xrel / WIN_WIDTH;
	w->pl.dir.x = w->pl.dir.x * cos(sign) - w->pl.dir.y * sin(sign);
	w->pl.dir.y = old_dir_x * sin(sign) + w->pl.dir.y * cos(sign);
	w->pl.plane.x = w->pl.plane.x * cos(sign) - w->pl.plane.y * sin(sign);
	w->pl.plane.y = old_pl_x * sin(sign) + w->pl.plane.y * cos(sign);
	//printf("mo_x%i  mo_y%i sign=%f \n", e.motion.xrel, e.motion.yrel, sign);
}

/*
** **************************************************************************
**	void ft_test_mv_p(t_wolf3d *w) | debug
**	Function to handle P button
** **************************************************************************
*/

void	ft_test_mv_p(t_wolf3d *w)
{
	printf("\npos x==%f  y==%f   ", w->pl.pos.x, w->pl.pos.y);
	printf("pl dir x==%f  y==%f\n", w->pl.dir.x , w->pl.dir.y);
	ft_enemy(w);
	//w->mouse_offset += 15;//camera up
	//ft_pl_stats(w);
	printf("P pressed\n");
}

/*
** **************************************************************************
**	void ft_test_mv_l(t_wolf3d *w) | debug
**	Function to handle L button
** **************************************************************************
*/

void	ft_test_mv_l(t_wolf3d *w)
{
	w->lol += 0.1;
	//w->mouse_offset -= 15;//camera down
	/*
	old
	w->pl.pos.x = 2;
	w->pl.pos.y = 2;
	w->draw_start -= 50;
	w->draw_end -= 50;
	w->line_height -= 10;
	*/
	printf("L pressed\n");
	return ;
	ft_door_print(w);//print all doors
}


/*
** **************************************************************************
**	void ft_door_print(t_wolf3d *w) | debug
**	Function to print all doors on map
** **************************************************************************
*/

void	ft_door_print(t_wolf3d *w)
{
	int	i;

	i = 0;
	while(i < w->map.doors_nbr)
	{
		printf("door#%d  x==%d y==%d   state==%d key==%d\n", \
		i, w->map.doors[i]->x, w->map.doors[i]->y, w->map.doors[i]->state, w->map.doors[i]->key);
		i++;
	}
}

/*
** **************************************************************************
**	void ft_init_doors(t_wolf3d *w) | debug
**	Function to print map
** **************************************************************************
*/

void	ft_print_map(t_wolf3d *w)
{
	int			*tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	tmp = w->map.map;
	while (i < w->map.m_hei)
	{
		j = 0;
		printf("\nm[%d]	", i);
		while (j < w->map.m_wid)
		{
			printf("[%d]==%d  ", j, tmp[j]);
			j++;
		}
		tmp += w->map.m_wid;
		i++;
	}
}
