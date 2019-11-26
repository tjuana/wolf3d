/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/26 21:33:19 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


/*
** **************************************************************************
**	static void	ft_door_print(t_wolf3d *w) | debug
**	Function to print all doors on map
** **************************************************************************
*/

static void	ft_door_print(t_wolf3d *w, int doors_nbr)
{
	int	i;

	i = 0;
	while(i < doors_nbr)
	{
		printf("door#%d  x==%d y==%d   state==%d key==%d\n", i, w->doors[i]->x, w->doors[i]->y, w->doors[i]->state, w->doors[i]->key);
		i++;
	}
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
		exit (EXIT_FAILURE);
	while (--drs >= 0)
		if (!(w->doors[drs] = malloc(sizeof(t_door))))
			exit (EXIT_FAILURE);
	return(res);
}

/*
** **************************************************************************
**	void ft_door_set(t_wolf3d *w)
**	Function to ser doors state
** **************************************************************************
*/

void		ft_door_set(t_wolf3d *w, int doors_nbr)
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
			if (tmp_map[j] == 17 && ++nbr < doors_nbr)
			{
				w->doors[nbr]->x = j;
				w->doors[nbr]->y = i;
				w->doors[nbr]->state = 0;
				w->doors[nbr]->key = 0;
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
	int	nbr;

	nbr = ft_door_nbr(w);
	printf("total doors==%i", nbr);
	ft_door_set(w, nbr);
	ft_door_print(w, nbr);
	//printf("ft_init_doors start hei=%d wid=%d\n", w->map.m_hei, w->map.m_wid);
	//ft_print_map(w);
	/**/
	//printf("ft_init_doors start %i\n", w->map.map[i]);
	//w->map.map
}

/*
** **************************************************************************
**	void ft_door_open(t_wolf3d *w)
**	Function to open doors
** **************************************************************************
*/

void		ft_door_open(t_wolf3d *w)
{
	printf("ft_open_door start\n");
	ft_door_create(w);
	return ;
}
