/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/25 18:37:38 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_init_doors(t_wolf3d *w)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	printf("ft_init_doors start\n");
	while (i < w->map.m_hei)
	{
		j = 0;
		printf("\nmap[%i]	", i);
		while (j < w->map.m_wid)
		{
			printf("[%i]==%i ", j, w->map.map[j]);
			j++;
		}
		w->map.map += w->map.m_wid;
		i++;
	}
	//printf("ft_init_doors start %i\n", w->map.map[i]);
	//w->map.map
}

/*
** **************************************************************************
**	void ft_open_door(t_wolf3d *w)
**	Function to open doors
** **************************************************************************
*/

void			ft_open_door(t_wolf3d *w)
{
	printf("ft_open_door start\n");
	ft_init_doors(w);
}
