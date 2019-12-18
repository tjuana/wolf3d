/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:33:34 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/18 14:15:20 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


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
	
	ft_load_png("/Textures/MFLR8_1.png", w.sdl);
	
	ft_load_textures(&w);
	
	// ft_bank_of_text("./Textures/", &w);
	
	ft_init_anim(&w);
	ft_init_view_map(&w);
	ft_init_sound(&w);
	//fpsinit();

	while (w.sdl->running)
	{
		ft_handle_events(&w);
		ft_use_events(&w);
		renderer(&w);
		
		//fpsthink();
	}
	
	ft_clean_sdl(&w);
	
	close(w.fd);
	
	return (0);
}

