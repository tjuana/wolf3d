/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:45:53 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/18 18:37:44 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

typedef struct			s_sprite
{
	t_coord				crd;
	double				distance;
	t_coord				dir;
	int					texture;
}						t_sprite;

typedef struct		    s_sprite_stats
{
	t_coord	            pos;
	t_coord				transform;
	double		        inv_det;
	int		        	screen_x;
	int		        	height;
	int		        	width;
	int		        	draw_starty;
	int		        	draw_startx;
	int		        	draw_endy;
	int		        	draw_endx;
	int		           	tex_x;
	int			        tex_y;
}   					t_sprite_stats;