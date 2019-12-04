/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:44:43 by dorange-          #+#    #+#             */
/*   Updated: 2019/11/30 15:01:33 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	void ft_check_map(t_map *map)
**	Function to check map's item
** **************************************************************************
*/

static int		ft_check_map_item(t_map *map, int i, int j, int empty_count)
{
	if ((i == 0 || i == (map->m_wid - 1)) ||
		(j == 0 || j == (map->m_hei - 1)))
	{
		if (map->map[j * map->m_wid + i] == 0 ||
			map->map[j * map->m_wid + i] >= 20)
			ft_error("Invalid map");
	}
	else
	{
		if (map->map[j * map->m_wid + i] == 0)
			empty_count++;
	}
	return (empty_count);
}

/*
** **************************************************************************
**	void ft_check_map(t_map *map)
**	Function to check maps
** **************************************************************************
*/

void		ft_check_map(t_map *map)
{
	int		i;
	int		j;
	int		empty_count;

	if (map->m_hei < 3 || map->m_wid < 3)
		ft_error("Invalid map");
	empty_count = 0;
	j = 0;
	while (j < map->m_hei)
	{
		i = 0;
		while (i < map->m_wid)
		{
			empty_count = ft_check_map_item(map, i, j, empty_count);
			i++;
		}
		j++;
	}
	if (empty_count == 0)
		ft_error("Invalid map");
}
