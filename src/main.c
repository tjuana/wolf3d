/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:33:34 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/10 15:21:44 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
# define DEG_30 0.52360

int	main(int c, char **v)
{
	t_wolf3d	w;

	// Set map type
	w.type = 0;
	if (c == 2)
		w.type = 1;
	if (c == 3 && ft_strcmp(v[2], "nmap"))
		w.type = 2;

	// Check arguments and file
	if (w.type < 1)
		ft_error("Error: wrong parameters");
	if ((w.fd = open(v[1], O_RDONLY)) < 0)
		ft_error("Error: bad file");

	ft_parser_nnmp(w.fd, &w);
	ft_print_sectors(w.sector); // check sector
	w.sdl = sdl_init(w.sdl);
	ft_init_wolf(&w);

	// ft_print_lines(&w); // Print the vertexes of lines
	// ft_print_sectors(w.sector);
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
	}
	ft_clean_sdl(&w);
	return (0);
}
