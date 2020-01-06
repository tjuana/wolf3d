/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:27:18 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/06 18:37:44 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		threading(t_wolf3d *w)
{
	int			x[2];
	pthread_t	threads[THREADS];
	t_threads	args[THREADS];

	x[0] = -1;
	x[1] = 0;
	while (++x[0] < THREADS)
	{
		args[x[0]].t1 = x[1];
		args[x[0]].t2 = x[1] + ((WIN_W / THREADS));
		args[x[0]].w1 = *w;
		ft_init_multi_wolf(&args[x[0]].w, w);
		pthread_create(&threads[x[0]], NULL, begin_game, (void*)&args[x[0]]) \
		!= 0 ? ft_error("threads create error") : 0;
		x[1] += (WIN_W / THREADS);
	}
	x[0] = -1;
	while (++x[0] < THREADS)
		pthread_join(threads[x[0]], NULL) != 0 ? \
		ft_error("threads join error") : 0;
	w->pl.pos.x = args[x[0] - 1].w.pl.pos.x;
	w->pl.pos.y = args[x[0] - 1].w.pl.pos.y;
	w->pl.plane.x = args[x[0] - 1].w.pl.plane.x;
	w->pl.plane.y = args[x[0] - 1].w.pl.plane.y;
	w->pl.dir.x = args[x[0] - 1].w.pl.dir.x;
	w->pl.dir.y = args[x[0] - 1].w.pl.dir.y;
	
	ft_draw_sprites(w);
}

void		*begin_game(void *w)
{
	t_threads *p;

	p = (t_threads *)w;
	while (p->t1 < p->t2)
	{
		ft_ray_dir_calculations(p);
		ft_wall_hit(p);
		ft_wall_draw_start(p);
		ft_draw_walls(p);
		ft_get_floor_coordinates(p);
		ft_draw_floor(p);
		ft_enemy(&p->w1, 0);
		p->t1++;
	}
	return (NULL);
}
