/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_wu_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:54:53 by dorange-          #+#    #+#             */
/*   Updated: 2019/11/14 17:23:55 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				ft_fdf_ipart(double x)
{
	return ((int)x);
}

double			ft_fdf_round(double x)
{
	return (ft_fdf_ipart(x + 0.5));
}

double			ft_fdf_fpart(double x)
{
	int			n;

	n = ft_fdf_ipart(x);
	x -= (double)n;
	return (x);
}

int				ft_fdf_get_color(int color1, int color2, double f1)
{
	t_fdf_get_color	c;
	int				rlt_color;

	c.r1 = (color1 & C_R) >> 16;
	c.g1 = (color1 & C_G) >> 8;
	c.b1 = (color1 & C_B);
	c.r2 = (color2 & C_R) >> 16;
	c.g2 = (color2 & C_G) >> 8;
	c.b2 = (color2 & C_B);
	if (c.r2 > c.r1)
		c.r_rez = c.r1 + (int)((f1) * (c.r2 - c.r1));
	else
		c.r_rez = c.r2 + (int)((1 - f1) * (c.r1 - c.r2));
	if (c.g2 > c.g1)
		c.g_rez = c.g1 + (int)((f1) * (c.g2 - c.g1));
	else
		c.g_rez = c.g2 + (int)((1 - f1) * (c.g1 - c.g2));
	if (c.b2 > c.b1)
		c.b_rez = c.b1 + (int)((f1) * (c.b2 - c.b1));
	else
		c.b_rez = c.b2 + (int)((1 - f1) * (c.b1 - c.b2));
	rlt_color = (c.r_rez << 16) + (c.g_rez << 8) + c.b_rez;
	return (rlt_color);
}
