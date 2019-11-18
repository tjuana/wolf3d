/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_wu_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:50:27 by dorange-          #+#    #+#             */
/*   Updated: 2019/11/14 16:55:45 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_fdf_plot(t_wolf3d *data, t_fdf_wu *wu, int x, int y)
{
	int		color;
	int		pos;
	double	o;

	wu->temp_f = 1 - wu->temp_f;
	if (wu->steps == 0)
		o = 0.0;
	else
		o = (double)wu->step / wu->steps;
	pos = x + (y * WIN_WIDTH);
	color = wu->color1;
	color = ft_fdf_get_color(color, (int)data->sdl->pixels[pos], wu->temp_f);
	if ((pos >= WIN_HEIGHT * WIN_WIDTH || pos < 0))
		return ;
	data->sdl->pixels[pos] = color;
}

void		ft_fdf_draw_line_first_pixels(t_wolf3d *data, t_fdf_wu **wu)
{
	if ((*wu)->steep)
	{
		(*wu)->temp_f = (1 - ft_fdf_fpart((*wu)->yend)) * (*wu)->xgap;
		ft_fdf_plot(data, *wu, (*wu)->ypxl1, (*wu)->xpxl1);
		(*wu)->temp_f = ft_fdf_fpart((*wu)->yend) * (*wu)->xgap;
		ft_fdf_plot(data, *wu, (*wu)->ypxl1 + 1, (*wu)->xpxl1);
	}
	else
	{
		(*wu)->temp_f = (1 - ft_fdf_fpart((*wu)->yend)) * (*wu)->xgap;
		ft_fdf_plot(data, *wu, (*wu)->xpxl1, (*wu)->ypxl1);
		(*wu)->temp_f = ft_fdf_fpart((*wu)->yend) * (*wu)->xgap;
		ft_fdf_plot(data, *wu, (*wu)->xpxl1, (*wu)->ypxl1 + 1);
	}
}

void		ft_fdf_draw_line_last_pixels(t_wolf3d *data, t_fdf_wu **wu)
{
	if ((*wu)->steep)
	{
		(*wu)->temp_f = (1 - ft_fdf_fpart((*wu)->yend)) * (*wu)->xgap;
		ft_fdf_plot(data, *wu, (*wu)->ypxl2, (*wu)->xpxl2);
		(*wu)->temp_f = ft_fdf_fpart((*wu)->yend) * (*wu)->xgap;
		ft_fdf_plot(data, *wu, (*wu)->ypxl2 + 1, (*wu)->xpxl2);
	}
	else
	{
		(*wu)->temp_f = (1 - ft_fdf_fpart((*wu)->yend)) * (*wu)->xgap;
		ft_fdf_plot(data, *wu, (*wu)->xpxl2, (*wu)->ypxl2);
		(*wu)->temp_f = ft_fdf_fpart((*wu)->yend) * (*wu)->xgap;
		ft_fdf_plot(data, *wu, (*wu)->xpxl2, (*wu)->ypxl2 + 1);
	}
}

void		ft_fdf_wu_cycle_x(t_wolf3d *data, t_fdf_wu *wu, double x)
{
	while (x <= wu->xpxl2 - 1)
	{
		wu->temp_f = 1 - ft_fdf_fpart(wu->intery);
		ft_fdf_plot(data, wu, x, ft_fdf_ipart(wu->intery));
		wu->temp_f = ft_fdf_fpart(wu->intery);
		ft_fdf_plot(data, wu, x, ft_fdf_ipart(wu->intery) + 1);
		wu->intery = wu->intery + wu->gradient;
		x++;
		wu->step++;
	}
}

void		ft_fdf_wu_cycle_y(t_wolf3d *data, t_fdf_wu *wu, double x)
{
	while (x <= wu->xpxl2 - 1)
	{
		wu->temp_f = 1 - ft_fdf_fpart(wu->intery);
		ft_fdf_plot(data, wu, ft_fdf_ipart(wu->intery), x);
		wu->temp_f = ft_fdf_fpart(wu->intery);
		ft_fdf_plot(data, wu, ft_fdf_ipart(wu->intery) + 1, x);
		wu->intery = wu->intery + wu->gradient;
		x++;
		wu->step++;
	}
}
