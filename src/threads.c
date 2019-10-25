/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:27:18 by tjuana            #+#    #+#             */
/*   Updated: 2019/10/25 14:00:04 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		threading(t_wolf3d *w)
{
	int			x;
	int			xx;
	pthread_t	threads[THREADS];
	t_threads	args[THREADS];

	x = -1;
	xx = 0;
	while (++x < THREADS)
	{
		args[x].t1 = xx;
		args[x].t2 = xx + ((WIN_WIDTH / THREADS));
		ft_init_multi_wolf(&args[x].w, w);
		pthread_create(&threads[x], NULL, begin_game, (void*)&args[x]);
		xx += (WIN_WIDTH / THREADS);
	}
	x = -1;
	while (++x < THREADS)
		pthread_join(threads[x], NULL);
	w->pl.pos.x = args[x - 1].w.pl.pos.x;
	w->pl.pos.y = args[x - 1].w.pl.pos.y;
	w->pl.plane.x = args[x - 1].w.pl.plane.x;
	w->pl.plane.y = args[x - 1].w.pl.plane.y;
	w->pl.dir.x = args[x - 1].w.pl.dir.x;
	w->pl.dir.y = args[x - 1].w.pl.dir.y;
	//ft_draw_sprites(w);
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
		//ft_get_floor_coordinates(p);
		//ft_draw_floor(p);
		p->t1++;
	}
	return (NULL);
	
}