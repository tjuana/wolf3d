/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_wu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:50:24 by dorange-          #+#    #+#             */
/*   Updated: 2019/11/14 17:04:10 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_fdf_init_wu(t_fdf_wu **wu, t_coord *dot_1, t_coord *dot_2)
{
	(*wu) = ft_memalloc(sizeof(t_fdf_wu));
	ft_bzero(*wu, sizeof(t_fdf_wu));
	(*wu)->x1 = dot_1->x + 0;
	(*wu)->y1 = dot_1->y + 0;
	(*wu)->x2 = dot_2->x + 0;
	(*wu)->y2 = dot_2->y + 0;
	(*wu)->color1 = 0xFFFF00;
}

void		ft_fdf_swap_double(double *n1, double *n2)
{
	double		p;

	p = *n1;
	*n1 = *n2;
	*n2 = p;
}

void		ft_fdf_draw_line_swap(t_fdf_wu **wu)
{
	if ((*wu)->steep)
	{
		ft_fdf_swap_double(&(*wu)->x1, &(*wu)->y1);
		ft_fdf_swap_double(&(*wu)->x2, &(*wu)->y2);
	}
	if ((*wu)->y2 < (*wu)->y1 || (*wu)->x1 > (*wu)->x2)
	{
		ft_fdf_swap_double(&(*wu)->x1, &(*wu)->x2);
		ft_fdf_swap_double(&(*wu)->y1, &(*wu)->y2);
	}
	if ((*wu)->x1 > (*wu)->x2)
	{
		ft_fdf_swap_double(&(*wu)->x1, &(*wu)->x2);
		ft_fdf_swap_double(&(*wu)->y1, &(*wu)->y2);
	}
}

void		ft_fdf_draw_line_param(t_wolf3d *data, t_fdf_wu **wu)
{
	(*wu)->dx = (*wu)->x2 - (*wu)->x1;
	(*wu)->dy = (*wu)->y2 - (*wu)->y1;
	(*wu)->gradient = (*wu)->dy / (*wu)->dx;
	if ((*wu)->dx == 0.0)
		(*wu)->gradient = 1.0;
	(*wu)->xend = ft_fdf_round((*wu)->x1);
	(*wu)->yend = (*wu)->y1 + (*wu)->gradient * ((*wu)->xend - (*wu)->x1);
	(*wu)->xgap = 1 - ft_fdf_fpart((*wu)->x1 + 0.5);
	(*wu)->xpxl1 = (*wu)->xend;
	(*wu)->ypxl1 = ft_fdf_ipart((*wu)->yend);
	ft_fdf_draw_line_first_pixels(data, wu);
	(*wu)->intery = (*wu)->yend + (*wu)->gradient;
	(*wu)->xend = ft_fdf_round((*wu)->x2);
	(*wu)->yend = (*wu)->y2 + (*wu)->gradient * ((*wu)->xend - (*wu)->x2);
	(*wu)->xgap = ft_fdf_fpart((*wu)->x2 + 0.5);
	(*wu)->xpxl2 = (*wu)->xend;
	(*wu)->ypxl2 = ft_fdf_ipart((*wu)->yend);
	ft_fdf_draw_line_last_pixels(data, wu);
}

void		ft_fdf_wu(t_coord *dot_1, t_coord *dot_2, t_wolf3d *data)
{
	t_fdf_wu	*wu;
	double		x;

	ft_fdf_init_wu(&wu, dot_1, dot_2);
	wu->steep = fabs(wu->y2 - wu->y1) > fabs(wu->x2 - wu->x1);
	ft_fdf_draw_line_swap(&wu);
	ft_fdf_draw_line_param(data, &wu);
	x = wu->xpxl1 + 1;
	wu->steps = wu->xpxl2 - x;
	wu->step = 0;
	if (wu->steep)
		ft_fdf_wu_cycle_y(data, wu, x);
	else
		ft_fdf_wu_cycle_x(data, wu, x);
	free(wu);
}
