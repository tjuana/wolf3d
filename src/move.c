/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:15:45 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/02 15:07:39 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_step_forward_check(t_wolf3d *w, unsigned char flag)
{
	// temp. check -> new rules for empty map -> need return 0
	if (w->map.map == NULL)
		return (1);
	if (flag == 1)
	{
		w->temp = w->map.map[(int)(w->pl.pos.x + w->pl.camera_vector.x * w->ms * 5)
		+ (int)w->pl.pos.y * w->map.m_wid];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	else if (flag == 0)
	{
		w->temp = w->map.map[(int)(w->pl.pos.y + w->pl.camera_vector.y * w->ms * 5)
		* w->map.m_wid + (int)w->pl.pos.x];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	return (0);
}

int		ft_step_back_check(t_wolf3d *w, unsigned char flag)
{
	// temp. check -> new rules for empty map -> need return 0
	if (w->map.map == NULL)
		return (1);
	if (flag == 1)
	{
		w->temp = w->map.map[(int)(w->pl.pos.x - w->pl.camera_vector.x * w->ms * 5)
		+ (int)w->pl.pos.y * w->map.m_wid];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	else if (flag == 0)
	{
		w->temp = w->map.map[(int)(w->pl.pos.y - w->pl.camera_vector.y * w->ms * 5)
		* w->map.m_wid + (int)w->pl.pos.x];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	return (0);
}
