/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/10 18:14:14 by drafe            ###   ########.fr       */
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
	while (++i < w->map.doors_nbr)
	{
		if (w->map.doors[i]->x == pl_x)
			if (((w->map.doors[i]->y == pl_y - 1) \
			|| (w->map.doors[i]->y == pl_y + 1)))
				break ;
		if (w->map.doors[i]->y == pl_y)
			if (((w->map.doors[i]->x == pl_x - 1) \
			|| (w->map.doors[i]->x == pl_x + 1)))
				break ;
	}
	i == w->map.doors_nbr ? i = -1 : 0;
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
	w->map.doors_nbr = drs;
	if ((drs > 0) && !(w->map.doors = (t_door**)malloc(sizeof(t_door*) * drs)))
		exit(EXIT_FAILURE);
	while (--drs >= 0)
		if (!(w->map.doors[drs] = malloc(sizeof(t_door))))
			exit(EXIT_FAILURE);
	return(w->map.doors_nbr);
}

/*
** **************************************************************************
**	void ft_door_set(t_wolf3d *w)
**	Function to set doors state
** **************************************************************************
*/

static void	ft_door_set(t_wolf3d *w)
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
			if (tmp_map[j] == 17 && ++nbr < w->map.doors_nbr)
			{
				w->map.doors[nbr]->x = j;
				w->map.doors[nbr]->y = i;
				w->map.doors[nbr]->state = 3;
				w->map.doors[nbr]->key = 0;
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
	w->map.doors_nbr = ft_door_nbr(w);
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
	d_nbr = -1;
	d_nbr = ft_door_exist(w);
	w->pl.st.door_nbr = d_nbr;
	if ((d_nbr >= 0) && (w->map.doors[d_nbr]->state == 3) && \
	(w->map.doors[d_nbr]->key == w->pl.st.key[d_nbr]))
	{
		//play door animation && sounds
		w->map.doors[d_nbr]->state = 1;
		printf("open door#%d\n", d_nbr);
	}
	return ;
}
