/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/10 21:43:31 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static void ft_enemy_left(t_wolf3d *w)
**	Function to move enemy left
** **************************************************************************
*/

static void	ft_enemy_left(t_wolf3d *w)
{
	int	move_flag;

	move_flag = 0;
	printf("\nw->lol==%f\n", w->lol);
	w->temp = w->map.map[(int)(w->map.sprite[0]->x - 0.2 * MOB_SPD * 15)\
	* w->map.m_wid + (int)w->map.sprite[0]->y];//distance to another block
	if (!w->temp || w->temp == 20)
		move_flag++;
	if (move_flag == 1)
		w->map.sprite[0]->x -= 0.2 * MOB_SPD;//speed
}

/*
** **************************************************************************
**	static void ft_enemy_right(t_wolf3d *w)
**	Function to move enemy right
** **************************************************************************
*/

static void	ft_enemy_right(t_wolf3d *w)
{
	int	move_flag;

	move_flag = 0;
	printf("\nw->lol==%d\n", ((int)(w->map.sprite[0]->x + 0.2 * MOB_SPD * 14) * w->map.m_wid + (int)w->map.sprite[0]->y));
	w->temp = w->map.map[(int)(w->map.sprite[0]->x + 0.2 * MOB_SPD * 14)\
	* w->map.m_wid + (int)w->map.sprite[0]->y];//distance to another block
	if (!w->temp || w->temp == 20)
		move_flag++;
	if (move_flag == 1)
		w->map.sprite[0]->x += 0.2 * MOB_SPD;//speed
}

/*
** **************************************************************************
**	static void ft_enemy_forward(t_wolf3d *w)
**	Function to move enemy forward
** **************************************************************************
*/

static void	ft_enemy_forward(t_wolf3d *w)
{
	int	move_flag;

	move_flag = 0;
	printf("\nw->lol==%f\n", w->lol);
	w->temp = w->map.map[(int)(w->map.sprite[0]->y + 0.2 * MOB_SPD * 15)\
	+ (int)w->map.sprite[0]->x * w->map.m_wid];//distance to another block
	if (!w->temp || w->temp == 20)
		move_flag++;
	if (move_flag == 1)
		w->map.sprite[0]->y += 0.2 * MOB_SPD;//speed
}

/*
** **************************************************************************
**	static void ft_enemy_back(t_wolf3d *w)
**	Function to move enemy back
** **************************************************************************
*/

static void	ft_enemy_back(t_wolf3d *w)
{
	int	move_flag;

	move_flag = 0;
	printf("\nw->lol==%f\n", w->lol);
	w->temp = w->map.map[(int)(w->map.sprite[0]->y - 0.2 * MOB_SPD * 15)\
	+ (int)w->map.sprite[0]->x * w->map.m_wid];//distance to another block
	if (!w->temp || w->temp == 20)
		move_flag++;
	if (move_flag == 1)
		w->map.sprite[0]->y -= 0.2 * MOB_SPD;//speed	
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
	ft_enemy_right(w);
	return ;
	ft_enemy_forward(w);
	ft_enemy_back(w);
	ft_enemy_left(w);
	//w->map.sprite[0]->y += 0.25;
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