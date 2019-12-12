/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/12 21:08:22 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static void ft_enemy_left(t_wolf3d *w)
**	Function to move enemy left
** **************************************************************************
*/

void	ft_enemy_left(t_wolf3d *w)
{
	int	move_flag;
	int	tst;

	move_flag = 0;
	printf("\n left x==%f y==%f ", w->map.sprite[0]->x, w->map.sprite[0]->y);
	tst = 0;
	tst = (int)(w->map.m_wid * (int)w->map.sprite[0]->y) + (w->map.sprite[0]->x - MOB_SPD - 0.5);
	w->temp = w->map.map[tst];
	printf(" w->tst==%d  w->map.map[tst]==%d\n",  tst, w->map.map[tst]);
	w->temp == 0 ? move_flag++ : 0;
	move_flag == 1 ? w->map.sprite[0]->x -= MOB_SPD : 0;
}

/*
** **************************************************************************
**	static void ft_enemy_right(t_wolf3d *w)
**	Function to move enemy right
** **************************************************************************
*/

void	ft_enemy_right(t_wolf3d *w)
{
	int	move_flag;
	int	tst;

	move_flag = 0;
	tst = 0;
	printf("\nright x==%f y==%f ", w->map.sprite[0]->x, w->map.sprite[0]->y);
	tst = (int)(w->map.m_wid * (int)w->map.sprite[0]->y) + (w->map.sprite[0]->x + MOB_SPD + 0.5);
	w->temp = w->map.map[tst];
	//x_wid = (int)(w->map.m_wid * w->map.sprite[0]->x);
	//y_wid = (int)(w->map.m_wid * w->map.sprite[0]->y);
	printf(" tst==%d  map[tst]==%d \n", tst, w->map.map[tst]);
	w->temp == 0 ? move_flag++ : 0;
	move_flag == 1 ? w->map.sprite[0]->x += MOB_SPD : 0;
}

/*
** **************************************************************************
**	static void ft_enemy_forward(t_wolf3d *w)
**	Function to move enemy forward
** **************************************************************************
*/

void	ft_enemy_forward(t_wolf3d *w)
{
	int	move_flag;
	int	tst;

	move_flag = 0;
	tst = 0;
	printf("\n forward x==%f y==%f ", w->map.sprite[0]->x, w->map.sprite[0]->y);
	tst = (int)((int)(w->map.sprite[0]->y + MOB_SPD + 0.5) * w->map.m_wid + w->map.sprite[0]->x);
	w->temp = w->map.map[tst];
	printf(" w->tst==%d  w->map.map[tst]==%d\n", tst, w->map.map[tst]);
	w->temp == 0 ? move_flag++ : 0;
	move_flag == 1 ? w->map.sprite[0]->y += MOB_SPD : 0;
}

/*
** **************************************************************************
**	static void ft_enemy_back(t_wolf3d *w)
**	Function to move enemy back
** **************************************************************************
*/

void	ft_enemy_back(t_wolf3d *w)
{
	int	move_flag;
	int	tst;

	move_flag = 0;
	printf("\n back x==%f y==%f m_wid==%d ", w->map.sprite[0]->x, w->map.sprite[0]->y, w->map.m_hei);
	tst = 0;
	tst = (int)((int)(w->map.sprite[0]->y - MOB_SPD - 0.5) * w->map.m_wid + w->map.sprite[0]->x);
	w->temp = w->map.map[tst];
	printf(" \n w->tst==%d  w->map.map[tst]==%d\n", tst, w->map.map[tst]);

	w->temp == 0 ? move_flag++ : 0;
	move_flag == 1 ? w->map.sprite[0]->y -= MOB_SPD : 0;
}

/*
** **************************************************************************
**	void ft_enemy(t_wolf3d *w)
**	Function to move enemy 
** **************************************************************************
*/

void		ft_enemy(t_wolf3d *w)
{
	int	i;
	int	j;
	int	*tmp_map;

	i = -1;
	j = -1;
	tmp_map = w->map.map;
	printf("x==%f y==%f\n", w->spr.pos.x, w->spr.pos.y);
	printf("mapx==%f mapy==%f\n", w->map.sprite[0]->x, w->map.sprite[0]->y);
	
	return ;
	ft_enemy_right(w);
	ft_enemy_forward(w);
	ft_enemy_back(w);
	ft_enemy_left(w);
	//w->map.sprite[0]->y += 0.55;
	/*printf("x==%f y==%f\n", w->spr.pos.x, w->spr.pos.y);

	w->spr.pos.x += 2.5;
	w->spr.pos.y += 2.5;
	printf("x2==%f y2==%f", w->spr.pos.x, w->spr.pos.y);
	while ((++i < w->map.m_hei) && (j = -1))
	{
		while (++j < w->map.m_wid)
			if (tmp_map[j] == 17)
				drs++;
		tmp_map += w->map.m_wid;
	}*/
	w->i += 0;
}