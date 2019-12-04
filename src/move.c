/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:15:45 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/29 15:17:16 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_step_forward_check(t_wolf3d *w, unsigned char flag)
{
	if (flag == 1)
	{
		w->temp = w->map.map[(int)(w->pl.pos.x + w->pl.dir.x * w->ms * 5)
		+ (int)w->pl.pos.y * w->map.m_wid];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	else if (flag == 0)
	{
		w->temp = w->map.map[(int)(w->pl.pos.y + w->pl.dir.y * w->ms * 5)
		* w->map.m_wid + (int)w->pl.pos.x];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	return (0);
}

int		ft_step_back_check(t_wolf3d *w, unsigned char flag)
{
	if (flag == 1)
	{
		w->temp = w->map.map[(int)(w->pl.pos.x - w->pl.dir.x * w->ms * 5)
		+ (int)w->pl.pos.y * w->map.m_wid];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	else if (flag == 0)
	{
		w->temp = w->map.map[(int)(w->pl.pos.y - w->pl.dir.y * w->ms * 5)
		* w->map.m_wid + (int)w->pl.pos.x];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	return (0);
}

int		ft_step_left_check(t_wolf3d *w, unsigned char flag)
{
	if (flag == 1)
	{
		w->temp = w->map.map[(int)(w->pl.pos.x + (-w->pl.dir.y) * w->ms * 5)
		+ (int)w->pl.pos.y * w->map.m_wid];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	else if (flag == 0)
	{
		w->temp = w->map.map[(int)(w->pl.pos.y + w->pl.dir.x * w->ms * 5)
		* w->map.m_wid + (int)w->pl.pos.x];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	return (0);
}

int		ft_step_right_check(t_wolf3d *w, unsigned char flag)
{
	if (flag == 1)
	{
		w->temp = w->map.map[(int)(w->pl.pos.x + w->pl.dir.y * w->ms * 5)
		+ (int)w->pl.pos.y * w->map.m_wid];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	else if (flag == 0)
	{
		w->temp = w->map.map[(int)(w->pl.pos.y + (-w->pl.dir.x) * w->ms * 5)
		* w->map.m_wid + (int)w->pl.pos.x];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	return (0);
}
