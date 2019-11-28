/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:15:45 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/27 21:23:29 by drafe            ###   ########.fr       */
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

/*int					ft_check_run(t_wolf3d *w)
{
	return ((w->arr[0] == 1) && !w->arr[1] && !w->arr[13] && ! w->arr[14]);
}*/
