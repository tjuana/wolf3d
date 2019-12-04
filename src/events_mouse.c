/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/04 21:02:36 by drafe            ###   ########.fr       */
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
	//w->mouse_offset += 15;//camera up
	ft_pl_stats(w);
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
	w->pl.st.f_sz = 32;
	ft_putstr_sdl(w, "0123456789", (WIN_WIDTH - 150) / 2, 0);
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
**	void	ft_door_print(t_wolf3d *w) | debug
**	Function to print all doors on map
** **************************************************************************
*/

void	ft_door_print(t_wolf3d *w)
{
	int	i;

	i = 0;
	while(i < w->doors_nbr)
	{
		printf("door#%d  x==%d y==%d   state==%d key==%d\n", \
		i, w->doors[i]->x, w->doors[i]->y, w->doors[i]->state, w->doors[i]->key);
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
    int window_w, window_h;
    int origin_x, origin_y;
    SDL_GetMouseState(x, y);
    // Translate mouse position from 'pixel' position into character position.
    // We are working here in screen coordinates and not pixels, since this is
    // what SDL_GetWindowSize() returns; we must calculate and subtract the
    // origin position since we center the image within the window.
    SDL_GetWindowSize(TXT_SDLWindow, &window_w, &window_h);
    origin_x = (window_w - screen_image_w) / 2;
    origin_y = (window_h - screen_image_h) / 2;
    *x = ((*x - origin_x) * TXT_SCREEN_W) / screen_image_w;
    *y = ((*y - origin_y) * TXT_SCREEN_H) / screen_image_h;
    if (*x < 0)
    {
        *x = 0;
    }
    else if (*x >= TXT_SCREEN_W)
    {
        *x = TXT_SCREEN_W - 1;
    }
    if (*y < 0)
    {
        *y = 0;
    }
    else if (*y >= TXT_SCREEN_H)
    {
        *y = TXT_SCREEN_H - 1;
    }
*/ 
