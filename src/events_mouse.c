/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/21 19:10:31 by drafe            ###   ########.fr       */
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
	double	old_dir_y;
	double	old_pl_y;
	double	mou_x;
	double	mou_y;
	double	sign;

	old_dir_x = w->pl.dir.x;
	old_pl_x = w->pl.plane.x;
	old_dir_y = w->pl.dir.y;
	old_pl_y = w->pl.plane.y;
	mou_x = e->motion.xrel;
	mou_y = e->motion.yrel;
	mou_x = mou_x / WIN_HEIGHT;
	mou_y = mou_y / WIN_HEIGHT;
	if (SDL_SetRelativeMouseMode(SDL_TRUE) != 0)
		ft_sdl_error(w);
	if (mou_y < 0)
	{
		w->mouse_offset += 15;
		//w->line_height += 30;
		//printf("w->line_height=%i\n", w->line_height);
		/*w->c.half_height -= 10;*/
		//w->draw_start += 10;
		//w->draw_end += 10;
		printf("mouse up\n");
	}
	else
	{
		w->mouse_offset -= 15;
		printf("mouse down\n");
	}
	printf("x:%f\n", w->pl.cameraX);
	sign = -w->rs;//w->r_speed = 0.1;
	if (mou_x < 0)
		sign = w->rs;//w->r_speed = 0.1;
	w->pl.dir.x = w->pl.dir.x * cos(sign) - w->pl.dir.y * sin(sign);
	w->pl.dir.y = old_dir_x * sin(sign) + w->pl.dir.y * cos(sign);
	w->pl.plane.x = w->pl.plane.x * cos(sign) - w->pl.plane.y * sin(sign);
	w->pl.plane.y = old_pl_x * sin(sign) + w->pl.plane.y * cos(sign);/*
	
	we calculate drawStart as -lineHeight / 2 + h / 2" and drawEnd as "lineHeight / 2 + h / 2".
	This makes the vertical center of the wall exactly match the vertical center of the screen.
	To change the vertical position of the camera without pitching,
	move everything vertically on the screen, that is, everything gets shifted up or down.
	t_coord		pos;
	t_coord		dir;
	t_coord		plane;
	t_coord		raydir;
	t_coord		side_dist;
	t_coord		delta_dist;
	double		old_dirX;
	double		old_planeX;
	double		cameraX;
	double		wall_dist;
	int			stepX;///?????
	int			stepY;
	int			side;
	*/
	//printf("%i %i sign=%f   w->r_speed=%f\n", e->motion.xrel, e->motion.yrel, sign, w->r_speed);
	return (1);
}

void			ft_test_mv_p(t_wolf3d *w)
{
	//w->mouse_offset += 15;
	//w->draw_start += 50;
	//w->draw_end += 50;
	
	//w->line_height += 10;
	printf("P pressed\n");
}

void			ft_test_mv_l(t_wolf3d *w)
{
	//w->mouse_offset -= 15;
	//w->draw_start -= 50;
	//	w->draw_end -= 50;
	//w->line_height -= 10;
	printf("L pressed\n");
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