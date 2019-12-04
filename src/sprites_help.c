/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:43:08 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/04 14:24:26 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void ft_swap_double(double *a, double *b)
{
	double	sw;

	sw = *a;
	*a = *b;
	*b = sw;
}

void    ft_sort(t_wolf3d *w)
{
    t_sort_util s;
	
	s.count = w->map.s_count;
	s.swap = 0;
	while (s.count > 1 || s.swap)
	{
		s.count = (s.count * 10) / 13;
		if (s.count == 9 || s.count == 10)
			s.count = 11;
		s.count < 1 ? s.count = 1 : 0;
		s.swap = 0;
		s.i = 0;
		s.j = 0;
		while (++s.i < w->map.s_count - s.count)
		{
			s.j = s.i + s.count;
			if (w->map.s_dst[s.i] < w->map.s_dst[s.j])
			{
				ft_swap_double(&w->map.s_dst[s.i], &w->map.s_dst[s.j]);
				ft_swap(&w->map.s_ord[s.i], &w->map.s_ord[s.j]);
				s.swap = 1;
			}
		}
	}
}