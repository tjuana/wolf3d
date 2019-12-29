/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:33:34 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/29 18:18:13 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_print_lines(t_wolf3d *w)
{
	t_list	*ptr_list;
	t_line	*ptr_line;
	int		i;

	ptr_list = w->line;
	i = 0;
	while (ptr_list)
	{
		// Get line values
		ptr_line = (t_line*)ptr_list->content;

		// Print the vertexes of line (straight line)
		printf(
			"LINE #%.2d\tx1: %.2f\ty1: %.2f\tx2: %.2f\ty2: %.2f\n",
			i,
			ptr_line->p1.x,
			ptr_line->p1.y,
			ptr_line->p2.x,
			ptr_line->p2.y
		);

		// Get next line
		ptr_list = ptr_list->next;
		i++;
	}
	exit(1);
}

int	main(int c, char **v)
{
	t_wolf3d	w;

	if (c != 2)
		ft_error("Error: wrong parameters");
	if ((w.fd = open(v[1], O_RDONLY)) < 0)
		ft_error("Error: bad file");
	read_file(w.fd, &w.map);
	w.sdl = sdl_init(w.sdl);
	ft_init_wolf(&w);
	// ft_print_lines(&w); // Print the vertexes of lines
	ft_load_textures(&w);
	ft_init_anim(&w);
	ft_init_view_map(&w);
	ft_init_sound(&w);
	fpsinit();
	while (w.sdl->running)
	{
		renderer(&w);
		ft_handle_events(&w);
		ft_use_events(&w);
		//fpsthink();
		printf("PL:\tx:%f\ty:%f\n", w.pl.pos.x, w.pl.pos.y);
		//sleep(10);
	}
	ft_clean_sdl(&w);
	return (0);
}
