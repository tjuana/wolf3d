/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:22:00 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/08 18:37:14 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "wolf3d.h"

typedef struct	s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct	s_player
{
	t_coord		pos;
	t_coord		dir;
	t_coord		plane;
	t_coord		raydir;
	t_coord		side_dist;
	t_coord		delta_dist;
	double		old_dirx;
	double		old_planex;
	double		camerax;
	double		wall_dist;
	int			stepx;
	int			stepy;
	int			side;
}				t_player;
#endif
