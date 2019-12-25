/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/25 20:34:11 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static void ft_enemy_set_dir(t_wolf3d *w, char dir, int res, int s_nbr)
**	Function to set enemy direction vector
** **************************************************************************
*/

static void	ft_enemy_set_dir(t_wolf3d *w, char dir, int res, int s_nbr)
{
	w->map.sprite[s_nbr]->dir.x = 1;
	w->map.sprite[s_nbr]->dir.y = 1;
	if ((dir == 'L') && (res = 2))
	{
		w->map.sprite[s_nbr]->pos.x -= MB_SPD;
		w->map.sprite[s_nbr]->dir.x = -1;
	}
	else if ((dir == 'R') && (res = 3))
	{
		w->map.sprite[s_nbr]->pos.x += MB_SPD;
		w->map.sprite[s_nbr]->dir.y = -1;
	}
	else if ((dir == 'F') && (res = 4))
		w->map.sprite[s_nbr]->pos.y += MB_SPD;
	else if ((dir == 'B') && (res = 5))
	{
		w->map.sprite[s_nbr]->pos.y -= MB_SPD;
		w->map.sprite[s_nbr]->dir.x = -1;
		w->map.sprite[s_nbr]->dir.y = -1;
	}
}

/*
** **************************************************************************
**	void ft_enemy_go(t_wolf3d *w, char dir)
**	Function to move enemy left, right, forward, back
** **************************************************************************
*/

int			ft_enemy_go(t_wolf3d *w, char dir, int s_nbr)
{
	int	res;
	int	pos;

	res = 0;
	pos = 0;
	dir == 'L' ? pos = (int)(w->map.m_wid * (int)w->map.sprite[s_nbr]->pos.y)\
		+ (w->map.sprite[s_nbr]->pos.x - MB_SPD - 0.5) : 0;
	dir == 'R' ? pos = (int)(w->map.m_wid * (int)w->map.sprite[s_nbr]->pos.y)\
		+ (w->map.sprite[s_nbr]->pos.x + MB_SPD + 0.5) : 0;
	dir == 'F' ? pos = (int)((int)(w->map.sprite[s_nbr]->pos.y \
	+ MB_SPD + 0.5) * w->map.m_wid + w->map.sprite[s_nbr]->pos.x) : 0;
	dir == 'B' ? pos = (int)((int)(w->map.sprite[s_nbr]->pos.y \
	- MB_SPD - 0.5) * w->map.m_wid + w->map.sprite[s_nbr]->pos.x) : 0;
	w->temp = w->map.map[pos];
	w->temp == 0 ? res++ : 0;
	dir == 'L' && res == 1 ? ft_enemy_set_dir(w, dir, res, s_nbr) : 0;
	dir == 'R' && res == 1 ? ft_enemy_set_dir(w, dir, res, s_nbr) : 0;
	dir == 'F' && res == 1 ? ft_enemy_set_dir(w, dir, res, s_nbr) : 0;
	dir == 'B' && res == 1 ? ft_enemy_set_dir(w, dir, res, s_nbr) : 0;
	return (res);
}

void		ft_enemy_cycle(t_wolf3d *w, int s_nbr)
{
	int	can_mv;

	if (w->map.sprite[s_nbr]->go == 0)
	{
		can_mv = ft_enemy_go(w, 'B', s_nbr);
		can_mv == 0 ? w->map.sprite[s_nbr]->go = 1 : 0;
	}
	else if (w->map.sprite[s_nbr]->go == 2)
	{
		can_mv = ft_enemy_go(w, 'F', s_nbr);
		can_mv == 0 ? w->map.sprite[s_nbr]->go = 3 : 0;
	}
	else if (w->map.sprite[s_nbr]->go == 1)
	{
		can_mv = ft_enemy_go(w, 'R', s_nbr);
		can_mv == 0 ? w->map.sprite[s_nbr]->go = 2 : 0;
	}
	else if (w->map.sprite[s_nbr]->go == 3)
	{
		can_mv = ft_enemy_go(w, 'L', s_nbr);
		can_mv == 0 ? w->map.sprite[s_nbr]->go = 0 : 0;
	}
}

/*
** **************************************************************************
**	void ft_enemy(t_wolf3d *w)
**	Function to move enemy
** **************************************************************************
*/

void		ft_enemy(t_wolf3d *w, int s_nbr)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	ft_enemy_detect_pl(w, s_nbr) == 1 ? ft_enemy_cycle(w, s_nbr) : 0;
}
