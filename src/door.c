/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/28 16:04:58 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static int	ft_door_exist(t_wolf3d *w)
**	Function to define doors in front of player
** **************************************************************************
*/

static int	ft_door_exist(t_wolf3d *w)
{
	int		i;
	int		pl_x;
	int		pl_y;

	i = -1;
	pl_x = (int)w->pl.pos.x;
	pl_y = (int)w->pl.pos.y;
	while (++i < w->doors_nbr)
	{
		if (w->doors[i]->x == pl_x)
			if (((w->doors[i]->y == pl_y - 1) || (w->doors[i]->y == pl_y + 1)))
				break ;
		if (w->doors[i]->y == pl_y)
			if (((w->doors[i]->x == pl_x - 1) || (w->doors[i]->x == pl_x + 1)))
				break ;
	}
	i == 12 ? i = -1 : 0;
	return (i);
}

/*
** **************************************************************************
**	int ft_door_nbr(t_wolf3d *w)
**	Function to countdown doors and malloc them
** **************************************************************************
*/

static int	ft_door_nbr(t_wolf3d *w)
{
	int	drs;
	int	res;
	int	*tmp_map;
	int	i;
	int	j;

	i = -1;
	j = -1;
	drs = 0;
	tmp_map = w->map.map;
	while ((++i < w->map.m_hei) && (j = -1))
	{
		while (++j < w->map.m_wid)
			if (tmp_map[j] == 17)
				drs++;
		tmp_map += w->map.m_wid;
	}
	res = drs;
	if ((drs > 0) && !(w->doors = (t_door**)malloc(sizeof(t_door*) * drs)))
		exit(EXIT_FAILURE);
	while (--drs >= 0)
		if (!(w->doors[drs] = malloc(sizeof(t_door))))
			exit(EXIT_FAILURE);
	return(res);
}

/*
** **************************************************************************
**	void ft_door_set(t_wolf3d *w)
**	Function to set doors state
** **************************************************************************
*/

void		ft_door_set(t_wolf3d *w)
{
	int	*tmp_map;
	int	nbr;
	int	i;
	int	j;

	i = -1;
	j = -1;
	nbr = -1;
	tmp_map = w->map.map;
	while ((++i < w->map.m_hei) && (j = -1))
	{
		while (++j < w->map.m_wid)
			if (tmp_map[j] == 17 && ++nbr < w->doors_nbr)
			{
				w->doors[nbr]->x = j;
				w->doors[nbr]->y = i;
				w->doors[nbr]->state = 3;
				w->doors[nbr]->key = 0;
				w->pl.st.key[nbr] = 0;
			}
		tmp_map += w->map.m_wid;
	}
}

/*
** **************************************************************************
**	void ft_door_init(t_wolf3d *w)
**	Function to init doors state
** **************************************************************************
*/

void		ft_door_create(t_wolf3d *w)
{
	w->doors_nbr = ft_door_nbr(w);
	//printf("total doors==%d", w->doors_nbr);
	ft_door_set(w);
	
	return ;
	ft_door_print(w);
	//ft_print_map(w);
}

/*
** **************************************************************************
**	void ft_door_open(t_wolf3d *w)
**	Function to open doors
** **************************************************************************
*/

void		ft_door_open(t_wolf3d *w)
{
	int		d_nbr;

	//printf("ft_open_door start\n");
	ft_door_create(w);
	d_nbr = ft_door_exist(w);
	if ((d_nbr >= 0) && (w->doors[d_nbr]->state == 3) && \
	(w->doors[d_nbr]->key == w->pl.st.key[d_nbr]))
	{
		//play animation && sounds
		w->doors[d_nbr]->state = 1;
		printf("open door#%d\n", d_nbr);
	}
	return ;
}

/*
	//printf("\n pl.x==%d pl.y==%d \n", (int)w->pl.pos.x, (int)w->pl.pos.y);
	while ((++i < w->doors_nbr) && (w->doors[i]->x != (int)w->pl.pos.x) && \
	(w->doors[i]->y != (int)w->pl.pos.y));
	printf("i==%d pos.x==%d pos.y==%d\n", i, (int)w->pl.pos.x, (int)w->pl.pos.y);

door#0  x==12 y==2   state==0 key==0
door#1  x==2 y==3   state==0 key==0
door#2  x==10 y==4   state==0 key==0
door#3  x==14 y==4   state==0 key==0
door#4  x==12 y==6   state==0 key==0
door#5  x==16 y==15   state==0 key==0
door#6  x==16 y==18   state==0 key==0
door#7  x==12 y==20   state==0 key==0
door#8  x==11 y==21   state==0 key==0
door#9  x==13 y==21   state==0 key==0
door#10  x==12 y==22   state==0 key==0
door#11  x==16 y==24   state==0 key==0
*/