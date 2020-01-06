/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:33:34 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/06 18:21:58 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
# define DEG_30 0.52360

/*
	void ft_iso_vertexes(t_wolf3d *w)
	
	Function that transform vertexes to isometric projection.
	It's a test function for map.
*/
void	ft_iso_vertexes(t_wolf3d *w)
{
	t_list		*ptr_list;
	t_sector	*ptr_sector;
	int			i;
	int			j;
	// for transform
	double		temp_x;
	double		temp_y;

	ptr_list = w->sector;
	i = 0;
	while (ptr_list)
	{
		// Get sector values
		ptr_sector = (t_sector*)ptr_list->content;

		j = 0;
		while (j < ptr_sector->vertex_count)
		{
			temp_x = ptr_sector->vertex[j]->x;
			temp_y = ptr_sector->vertex[j]->y;

			// ptr_sector->vertex[j]->x = (temp_x) * cos(1) - (temp_y) * sin(1);
			// ptr_sector->vertex[j]->y = (temp_x) * sin(1) + (temp_y) * cos(1);

			// origin iso. transform
			//ptr_sector->vertex[j]->x = ((temp_x) - (temp_y)) * cos(DEG_30);
			//ptr_sector->vertex[j]->y = ((temp_x) + (temp_y)) * sin(DEG_30);
			j++;
		}

		// Get next sector
		ptr_list = ptr_list->next;
		i++;
	}
}

/*
	void ft_print_sectors(t_list *ptr_list)
	
	Function that print the map sectors.
*/
void	ft_print_sectors(t_list *ptr_list)
{
	// t_list		*ptr_list;
	t_sector	*ptr_sector;
	int			i;
	int			j;

	// ptr_list = w->sector;
	i = 0;
	while (ptr_list)
	{
		// Get sector values
		ptr_sector = (t_sector*)ptr_list->content;

		j = 0;
		while (j < ptr_sector->vertex_count)
		{
			// Print the vertexes of sector
			printf(
				"SECTOR #%.2d\tVERTEX #%.2d\tx: %6.2f\ty: %6.2f\n",
				i,
				j,
				ptr_sector->vertex[j]->x,
				ptr_sector->vertex[j]->y
			);
			j++;
		}

		// Get next sector
		ptr_list = ptr_list->next;
		i++;
	}
}

/*
	void ft_print_lines(t_wolf3d *w)
	
	Function that print the vertexes of lines.
*/
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
}

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

	// Get map
	if (w.type == 1)
		read_file(w.fd, &w.map);
	else
		ft_read_file_nmp(w.fd, &w);

	w.sdl = sdl_init(w.sdl);
	ft_init_wolf(&w);
	// ft_print_lines(&w); // Print the vertexes of lines
	// ft_print_sectors(w.sector);
	// ft_iso_vertexes(&w); // Transform vertexes to isometric projection (for map) [test]
	// exit(1);
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
		// ft_get_player_sector(&w);
		// printf("PLAYER SECTOR: %d,     PLAYER COORD.: x_%5.2f, y_%5.2f\n", ft_get_player_sector(&w), w.pl.pos.x, w.pl.pos.y);
		//fpsthink();
		//printf("PL:\tx:%f\ty:%f\n", w.pl.pos.x, w.pl.pos.y);
		//sleep(10);
	}
	ft_clean_sdl(&w);
	return (0);
}
