/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/06 18:30:14 by drafe            ###   ########.fr       */
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
	mou_x /= WIN_H;
	if (w->pl.menu == 0)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE) != 0 ? ft_sdl_error(w) : 0;
		sign = -w->rs;
		if (mou_x < 0)
			sign = w->rs;
		sign -= e.motion.xrel / WIN_W;
		w->pl.dir.x = w->pl.dir.x * cos(sign) - w->pl.dir.y * sin(sign);
		w->pl.dir.y = old_dir_x * sin(sign) + w->pl.dir.y * cos(sign);
		w->pl.plane.x = w->pl.plane.x * cos(sign) - w->pl.plane.y * sin(sign);
		w->pl.plane.y = old_pl_x * sin(sign) + w->pl.plane.y * cos(sign);
	}
	else
		SDL_SetRelativeMouseMode(SDL_FALSE) != 0 ? ft_sdl_error(w) : 0;
	//w->mouse_offset -= e->motion.yrel;//up and down
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
	printf("\npl_pos:	x==%f  y==%f \n", w->pl.pos.x, w->pl.pos.y);
	printf("pl_dir:	x==%f  y==%f \n", w->pl.dir.x, w->pl.dir.y);
	printf("sp_pos:	x==%f  y==%f \n", w->spr.pos.x, w->spr.pos.y);
	printf("map_sp_pos:	x==%f  y==%f \n", w->map.sprite[0]->pos.x, w->map.sprite[0]->pos.y);
	//w->mouse_offset += 15;//camera up
	//ft_pl_stats(w);
	printf("P pressed\n");
	//SDL_RenderClear(w->sdl->renderer);
	//SDL_UpdateTexture(w->sdl->text, 0, w->sdl->pixels, WIN_WIDTH * 4);
	//SDL_RenderCopy(w->sdl->renderer, w->sdl->text, NULL, NULL);
}

/*
** **************************************************************************
**	void ft_test_mv_l(t_wolf3d *w) | debug
**	Function to handle L button
** **************************************************************************
*/

void	ft_test_mv_l(t_wolf3d *w)
{
	w->pl.menu = 0;
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

/*
** **************************************************************************
**	void ft_test_kp2(t_wolf3d *w) | debug
**	Function to handle numpad 2 button
** **************************************************************************
*/

void	ft_test_kp2(t_wolf3d *w)
{
	ft_enemy_go(w, 'B', 0);		
}

/*
** **************************************************************************
**	void ft_test_kp4(t_wolf3d *w) | debug
**	Function to handle numpad 4 button
** **************************************************************************
*/

void	ft_test_kp4(t_wolf3d *w)
{
	ft_enemy_go(w, 'L', 0);
}

/*
** **************************************************************************
**	void ft_test_kp6(t_wolf3d *w) | debug
**	Function to handle numpad 6 button
** **************************************************************************
*/

void	ft_test_kp6(t_wolf3d *w)
{
	ft_enemy_go(w, 'R', 0);
}

/*
** **************************************************************************
**	void ft_test_kp8(t_wolf3d *w) | debug
**	Function to handle numpad 8 button
** **************************************************************************
*/

void	ft_test_kp8(t_wolf3d *w)
{
	printf("PRESS 8  res==\n");
	w->temp += 0;
	//ft_enemy_go(w, 'F', 0);
}
