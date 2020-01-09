/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:17:47 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/09 14:51:25 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
	ft_free_array2(char **array, count)

	Function that free array elements.
*/
void		ft_free_array2(void **array, int count)
{
	void	**ptr_array;
	void	*ptr_array_elem;
	int		i;

	if (array == NULL)
		return ;
	i = 0;
	while(i < count)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*
	t_vector3 *ft_parse_vertex(char *str)

	Function that parsing string and return vertex.
*/
/*t_vector3		*ft_parse_vertex(char **ptr)
{
	t_vector3	*p;

	p = malloc(sizeof(t_vector3));

	(*ptr) = ft_strchr((*ptr), '{');
	(*ptr)++;
	p->x = (double)ft_atoi((*ptr));
	(*ptr) = ft_strchr((*ptr), ',');
	(*ptr)++;
	p->y = (double)ft_atoi((*ptr));
	// for transformation
	p->z = 0;
	p->w = 0;
	return(p);
}*/

/*
	int ft_get_vertexes_count(char *str)

	Function that parsing string and return vertexes
	count or -1 if map invalid.
*/
/*int			ft_get_vertexes_count(char *str)
{
	char			*ptr;
	int				count[3];

	ft_bzero(count, sizeof(int) * 3);
	ptr = ft_strchr(str, '{');
	while (ptr != NULL && *ptr != '\0')
	{
		count[0]++;

		ptr++;
		ptr = ft_strchr(ptr, ',');
		if (*ptr == ',')
			count[1]++;

		ptr++;
		ptr = ft_strchr(ptr, '}');
		if (*ptr == '}')
			count[2]++;

		ptr++;
		ptr = ft_strchr(ptr, '{');
	}

	if (count[0] != count[1] ||
		count[1] != count[2] ||
		count[2] != count[0])
		return (-1);
	return (count[0]);
}*/

void	ft_copy_sector(t_wolf3d *w, t_vector3 **vertex, t_list **ptr, int count)
{
	int			i;
	t_sector	*new_sector;
	t_vector3	**p;
	t_list		*list_item;

	new_sector = ft_my_malloc(sizeof(t_sector));
	p = ft_my_malloc(sizeof(void*) * count);

	// Copy all values
	i = 0;
	while (i < count)
	{
		p[i] = ft_my_malloc(sizeof(t_vector3));
		p[i]->x = vertex[i]->x;
		p[i]->y = vertex[i]->y;
		p[i]->z = vertex[i]->z;
		p[i]->w = vertex[i]->w;
		i++;
	}
	
	new_sector->vertex = p;
	new_sector->vertex_count = count;
	list_item = ft_lstnew(new_sector, sizeof(t_sector));
	if (*ptr == NULL)
		*ptr = list_item;
	else
		ft_lstadd(ptr, list_item);

	// намудрил с указателями
}

/*
	void ft_sector_set_neighborhood(t_wolf3d *w)

	Function that search and set neighborhood sectors.
*/
void	ft_sector_set_neighborhood(t_wolf3d *w)
{
	int	*sectors;
}

// Set sector
void	ft_set_sector(t_wolf3d *w, t_vector3 **vertex, int count, double floor, double height, int color)
{
	t_sector	*new_sector;
	t_vector3	**p;
	t_list		*list_item;
	int			i;

	new_sector = ft_my_malloc(sizeof(t_sector));
	new_sector->vertex = vertex;
	new_sector->vertex_count = count;
	new_sector->floor = floor;
	// new_sector->height = height;
	new_sector->height = height * (WIN_HEIGHT / 10);
	new_sector->color = color;
	list_item = ft_lstnew(new_sector, sizeof(t_sector));
	if (w->sector == NULL)
		w->sector = list_item;
	else
		ft_lstadd(&(w->sector), list_item);

	// search neighborhood sectors
	ft_sector_set_neighborhood(w);

	ft_copy_sector(w, vertex, &w->map_sector, count); // for sector vertexes
	ft_copy_sector(w, vertex, &w->map_sector_top, count);
}

/*
	void ft_parsing_vertexes(t_wolf3d *w, char *str)

	Function that parsing string and set vertexes.
*/
void		ft_parsing_vertexes(t_wolf3d *w, char *str, double floor, double height, int color)
{
	t_vector3			**vertex;
	int				count;
	unsigned int	i;
	// temp
	t_list	*lst;
	char	*ptr;

	ptr = str;
	count = ft_get_vertexes_count(str);
	if (count < 2)
		ft_error("map is failed");

	vertex = malloc(sizeof(void*) * count);
	i = 0;
	while (i < count)
	{
		vertex[i] = ft_parse_vertex(&ptr);
		i++;
	}

	// Set sector (new way)
	ft_set_sector(w, vertex, count, floor, height, color);
}

/*
	void ft_parsing_sector_param(char *str, double floor, double height)

	Function that parsing special param. for sector.
*/
void		ft_parsing_sector_param(char *str, double *floor, double *height, int *color)
{
	*floor = ft_atoi(str);
	str = ft_strchr(str, ' ');
	if (str == NULL)
		ft_error("INCORRECT MAP\n");
	str++;
	*height = ft_atoi(str);
	str = ft_strchr(str, ' ');
	if (str == NULL)
	{
		*color = 0x120a8f;
		return;
	}
	str++;

	*color = strtol(str, NULL, 16);
	//ft_error("INCORRECT MAP\n");
}

/*
	void ft_read_file_nmp(int fd, t_wolf3d *w)

	Function that read the file in .nmp format.
*/
void		ft_read_file_nmp(int fd, t_wolf3d *w)
{
	char	*line;
	int		sector_count;
	int		res;
	char	**map;
	char	**temp_map;
	double	floor;
	double	height;
	int		color;

	sector_count = 0;
	while ((res = get_next_line(fd, &line)) > 0)
	{
		map = ft_strsplit(line, '\t');
		if (!ft_strcmp(map[0], "sector"))
		{
			ft_parsing_sector_param(map[1], &floor, &height, &color);
			// temp_map = ft_strsplit(map[1], ' ');
			// need to set walls height
			// free temp_map
			
			// need to set walls coord.

			// for example, let's write the walls in a line (minor version)
			ft_parsing_vertexes(w, map[2], floor, height, color);
		}
		// free map
		ft_free_array2((void**)map, 3);
		// parser?
		sector_count++;
		free(line);
	}
	free(line);
}
