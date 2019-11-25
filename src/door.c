/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/25 21:28:33 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	void ft_init_doors(t_wolf3d *w)
**	Function to print map
** **************************************************************************
*/

void	ft_print_map(t_wolf3d *w)
{
	int			*tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	tmp = w->map.map;
	while (i < w->map.m_hei)
	{
		j = 0;
		printf("\nm[%d]	", i);
		while (j < w->map.m_wid)
		{
			printf("[%d]==%d  ", j, tmp[j]);
			j++;
		}
		tmp += w->map.m_wid;
		i++;
	}
}

/*
** **************************************************************************
**	void ft_init_doors(t_wolf3d *w)
**	Function to init doors state
** **************************************************************************
*/

void	ft_init_doors(t_wolf3d *w)
{
	int			*tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	tmp = w->map.map;
	printf("ft_init_doors start hei=%d wid=%d\n", w->map.m_hei, w->map.m_wid);
	while (i < w->map.m_hei)
	{
		j = 0;
		//printf("\nm[%d]	", i);
		while (j < w->map.m_wid)
		{
			//printf("[%d]==%d  ", j, tmp[j]);
			if (tmp[j] == 17)
			{
				//printf("its door!\n");
			}
			j++;
		}
		tmp += w->map.m_wid;
		i++;
	}
	/**/
	//printf("ft_init_doors start %i\n", w->map.map[i]);
	//w->map.map
}

/*
** **************************************************************************
**	void ft_open_door(t_wolf3d *w)
**	Function to open doors
** **************************************************************************
*/

void	ft_open_door(t_wolf3d *w)
{
	printf("ft_open_door start\n");
	ft_init_doors(w);
	return ;
	
}
