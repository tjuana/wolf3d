/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:03:17 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/17 20:03:36 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

typedef struct			s_fdf_wu
{
	double				x1;
	double				y1;
	double				x2;
	double				y2;
	double				p;
	double				dx;
	double				dy;
	double				gradient;
	double				xend;
	double				yend;
	double				xgap;
	double				xpxl1;
	double				ypxl1;
	double				xpxl2;
	double				ypxl2;
	double				intery;
	int					steep;
	int					steps;
	int					step;
	int					color1;
	int					color2;
	int					check_color_rev;
	double				temp_f;
}						t_fdf_wu;

typedef struct			s_fdf_get_color
{
	int					color1;
	int					color2;
	double				f1;
	int					r1;
	int					g1;
	int					b1;
	int					r2;
	int					g2;
	int					b2;
	int					r_rez;
	int					g_rez;
	int					b_rez;
}						t_fdf_get_color;