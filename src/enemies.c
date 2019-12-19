/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/19 12:22:32 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_enemy_cycle(t_wolf3d *w)
{
	int	i;
	int	can_mv;

	i = 999;
	while (i--)
	{
		can_mv = ft_enemy_go(w, 'B');
		
	}	
	i = 999;
	while (i--)
	{
		can_mv = ft_enemy_go(w, 'F');
		ft_enemy(w);
	}
		
}

/*
** **************************************************************************
**	void ft_enemy(t_wolf3d *w)
**	Function to move enemy
** **************************************************************************
*/

void	ft_enemy(t_wolf3d *w)
{
	int	i;
	int	j;
	int	*tmp_map;

	i = -1;
	j = -1;
	tmp_map = w->map.map;
	ft_enemy_detect_pl(w);
	return ;
	

	w->i += 0;
}

/*

-find player pos+
-range of view
-move in 4 directions+
-dont move through blocks+
-player cant pass through enemy
-move from point to point
-move with obstacles

-dead
-waiting
-shooting



*/