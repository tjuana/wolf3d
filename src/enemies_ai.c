/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_ai.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/25 20:53:46 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	void ft_enemy_chase(t_wolf3d *w, int s_nbr)
**	Function helps enemy go to player pos
** **************************************************************************
*/

static void	ft_enemy_chase(t_wolf3d *w, int s_nbr)
{
	double	pos_add;
	double	pos_sub;
	int		res;

	pos_add = 0;
	pos_sub = 0;
	res = 0;
	pos_add = w->map.sprite[s_nbr]->pos.x + MB_SPD + 0.5;
	pos_sub = w->map.sprite[s_nbr]->pos.x - MB_SPD - 0.5;
	if (w->pl.pos.x > pos_add)
		res = ft_enemy_go(w, 'R', s_nbr);
	else if (w->pl.pos.x < pos_sub)
		res = ft_enemy_go(w, 'L', s_nbr);
	pos_add = w->map.sprite[s_nbr]->pos.y + MB_SPD + 0.5;
	pos_sub = w->map.sprite[s_nbr]->pos.y - MB_SPD - 0.5;
	//w->map.sprite[s_nbr]->go = res;
	if (w->pl.pos.y > pos_add)
		res = ft_enemy_go(w, 'F', s_nbr);
	else if (w->pl.pos.y < pos_sub)
		res = ft_enemy_go(w, 'B', s_nbr);
	//res != 0 ? w->map.sprite[s_nbr]->go = res : 10;
}

/*
** **************************************************************************
**	void ft_enemy_go(t_wolf3d *w)
**	Function helps enemy find player
** **************************************************************************
*/

/*
		distance to player in double
		w->map.sprite[s_nbr]->dist = sqrt(pow((view_vec.x), 2) + \
		pow((view_vec.y), 2));
		printf("\n dirx==%f diry==%f   detect==%i\n", w->map.sprite[s_nbr]->dir.x, w->map.sprite[s_nbr]->dir.y, detect);
*/

int			ft_enemy_detect_pl(t_wolf3d *w, int s_nbr)
{
	t_coord	view_vec;

	view_vec.x = w->pl.pos.x - w->map.sprite[s_nbr]->pos.x;
	view_vec.y = w->pl.pos.y - w->map.sprite[s_nbr]->pos.y;
	w->map.sprite[s_nbr]->det = (view_vec.x * w->map.sprite[s_nbr]->dir.x) + \
	(view_vec.y * w->map.sprite[s_nbr]->dir.y);
	if ((w->map.sprite[s_nbr]->det > -MB_DET) && (w->map.sprite[s_nbr]->det < MB_DET))
	{
		ft_enemy_chase(w, s_nbr);
		return(0);
		//printf("\nYOU ARE DETECTED by enemy#%d \n", s_nbr);
	}
	return(1);
}
