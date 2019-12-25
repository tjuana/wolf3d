/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:45:53 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/25 20:42:19 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

typedef struct	s_sprite
{
	t_coord		pos;
	t_coord		dir;
	double		dist;
	int			texture;
	int			go;
	double		det;
}				t_sprite;

typedef struct	s_sprite_stats
{
	t_coord		pos;
	t_coord		transform;
	double		inv_det;
	int			screen_x;
	int			height;
	int			width;
	int			draw_starty;
	int			draw_startx;
	int			draw_endy;
	int			draw_endx;
	int			tex_x;
	int			tex_y;
}				t_sprite_stats;