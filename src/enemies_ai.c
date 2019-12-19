/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_ai.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/18 21:22:26 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_enemy_set_dir(t_wolf3d *w, char dir, int res)
{
	if (dir == 'L')
	{
		w->map.sprite[0]->crd.x -= MOB_SPD;
		w->map.sprite[0]->dir.x = -1;
		w->map.sprite[0]->dir.y = 1;
		res = 2;
	}
	else if (dir == 'R')
	{
		w->map.sprite[0]->crd.x += MOB_SPD;
		w->map.sprite[0]->dir.x = 1;
		w->map.sprite[0]->dir.y = -1;
		res = 3;
	}
	else if (dir == 'F')
	{
		w->map.sprite[0]->crd.y += MOB_SPD;
		w->map.sprite[0]->dir.x = 1;
		w->map.sprite[0]->dir.y = 1;
		res = 4;
	}
	else if (dir == 'B')
	{
		w->map.sprite[0]->crd.y -= MOB_SPD;
		w->map.sprite[0]->dir.x = -1;
		w->map.sprite[0]->dir.y = -1;
		res = 5;
	}
}

/*
** **************************************************************************
**	void ft_enemy_go(t_wolf3d *w, char dir)
**	Function to move enemy left, right, forward, back
** **************************************************************************
*/

int		ft_enemy_go(t_wolf3d *w, char dir)
{
	int	res;
	int	pos;

	res = 0;
	pos = 0;
	dir == 'L' ? pos = (int)(w->map.m_wid * (int)w->map.sprite[0]->crd.y) \
		+ (w->map.sprite[0]->crd.x - MOB_SPD - 0.5) : 0;
	dir == 'R' ? pos = (int)(w->map.m_wid * (int)w->map.sprite[0]->crd.y) \
		+ (w->map.sprite[0]->crd.x + MOB_SPD + 0.5) : 0;
	dir == 'F' ? pos = (int)((int)(w->map.sprite[0]->crd.y + MOB_SPD + 0.5) \
		* w->map.m_wid + w->map.sprite[0]->crd.x) : 0;
	dir == 'B' ? pos = (int)((int)(w->map.sprite[0]->crd.y - MOB_SPD - 0.5) \
		* w->map.m_wid + w->map.sprite[0]->crd.x) : 0;
	w->temp = w->map.map[pos];
	w->temp == 0 ? res++ : 0;
	dir == 'L' && res == 1 ? ft_enemy_set_dir(w, dir, res) : 0;
	dir == 'R' && res == 1 ? ft_enemy_set_dir(w, dir, res) : 0;
	dir == 'F' && res == 1 ? ft_enemy_set_dir(w, dir, res) : 0;
	dir == 'B' && res == 1 ? ft_enemy_set_dir(w, dir, res) : 0;
	return (res);
}

/*
** **************************************************************************
**	void ft_enemy_go(t_wolf3d *w)
**	Function helps enemy find player
** **************************************************************************
*/

void	ft_enemy_detect_pl(t_wolf3d *w)
{
	t_coord	view_vec;
	int		detect;

	detect = 0;
	view_vec.x = w->pl.pos.x - w->map.sprite[0]->crd.x;
	view_vec.y = w->pl.pos.y - w->map.sprite[0]->crd.y;
	detect = (view_vec.x * w->map.sprite[0]->dir.x) + (view_vec.y * w->map.sprite[0]->dir.y);
	//printf("detect==%i dist==%f", detect, w->map.sprite[0]->distance);
	if (detect == 1 && w->map.sprite[0]->distance < 5)
		printf("\nYOU ARE DETECTED\n");
	w->temp += 0;
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
