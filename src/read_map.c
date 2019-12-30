/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:17:47 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/30 17:01:17 by dorange-         ###   ########.fr       */
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
	t_coord *ft_parse_vertex(char *str)

	Function that parsing string and return vertex.
*/
t_coord		*ft_parse_vertex(char **ptr)
{
	t_coord	*p;

	p = malloc(sizeof(t_coord));

	(*ptr) = ft_strchr((*ptr), '{');
	(*ptr)++;
	p->x = (double)atof((*ptr));
	(*ptr) = ft_strchr((*ptr), ',');
	(*ptr)++;
	p->y = (double)atof((*ptr));
	return(p);
}

/*
	int ft_get_vertexes_count(char *str)

	Function that parsing string and return vertexes
	count or -1 if map invalid.
*/
int			ft_get_vertexes_count(char *str)
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
}

/*
	void ft_parsing_vertexes(t_wolf3d *w, char *str)

	Function that parsing string and set vertexes.
*/
void		ft_parsing_vertexes(t_wolf3d *w, char *str)
{
	t_coord			**vertex;
	int				count;
	unsigned int	i;
	// temp
	t_line	temp_line;
	t_line	*line;
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

	i = 0;
	while (i < count)
	{
		// Print sector vertexes
		printf("VERTEX #%.2d\tx: %.2f\ty: %.2f\n", i, vertex[i]->x, vertex[i]->y);
		i++;
	}

	// Set line (temp)
	temp_line.height = WIN_HEIGHT; // standart height
	i = 0;
	while (i + 1 < count)
	{
		temp_line.p1.x = vertex[i]->x;
		temp_line.p1.y = vertex[i]->y;
		temp_line.p2.x = vertex[i + 1]->x;
		temp_line.p2.y = vertex[i + 1]->y;
		// printf("CURRENT LINE %.2d: %.2f, %.2f, %.2f, %.2f\n", i, temp_line.p1.x, temp_line.p1.y, temp_line.p2.x, temp_line.p2.y);
		ft_set_line(w, line, temp_line, lst);
		i++;
	}

	// Finish
	temp_line.p1.x = vertex[count - 1]->x;
	temp_line.p1.y = vertex[count - 1]->y;
	temp_line.p2.x = vertex[0]->x;
	temp_line.p2.y = vertex[0]->y;
	
	ft_set_line(w, line, temp_line, lst);
	i++;


	ft_free_array2((void**)vertex, count);
}
/*
	void ft_read_file_nmp(int fd, t_wolf3d *w)

	Function that read the file in .nmp format.
*/
void		ft_read_file_nmp(int fd, t_wolf3d *w)
{
	char	*line;
	int		len;
	int		res;
	char	**map;
	char	**temp_map;

	len = 0;
	while ((res = get_next_line(fd, &line)) > 0)
	{
		map = ft_strsplit(line, '\t');
		if (!ft_strcmp(map[0], "sector"))
		{
			// temp_map = ft_strsplit(map[1], ' ');
			// need to set walls height
			// free temp_map
			
			// need to set walls coord.

			// for example, let's write the walls in a line (minor version)
			ft_parsing_vertexes(w, map[2]);
		}
		// free map
		ft_free_array2((void**)map, 3);
		// parser?
		len++;
		free(line);
	}
	free(line);
}

void		read_file(int fd, t_map *map)
{
	t_list	*lst;
	int		lenght;

	lst = NULL;
	lenght = get_lines(fd, &lst);
	if (lst == NULL)
		ft_error("Map is empty");
	get_map(map, ft_countwords(lst->content, ' '), ft_lstcount(lst));
	map->s_count = write_map(map, lst);
	if (map->s_count)
	{
		write_sprites(map);
		map->s_ord = ft_my_malloc(sizeof(int) * map->s_count);
		map->s_dst = ft_my_malloc(sizeof(double) * map->s_count);
	}
}

int			get_lines(int fd, t_list **lst)
{
	t_list	*tmp;
	char	*line;
	int		len;
	int		width;
	int		res;

	len = 0;
	width = -1;
	while ((res = get_next_line(fd, &line)) > 0)
	{
		width == -1 ? width = ft_countwords(line, ' ') : 0;
		width != ft_countwords(line, ' ') ? ft_error("Error map") : 0;
		if (!(tmp = ft_lstnew(line, ft_strlen(line) + 1)))
			ft_error("MAlloc failed");
		ft_lstadd(lst, tmp);
		ft_strdel(&line);
		len++;
		free(line);
	}
	free(line);
	res < 0 ? ft_error("Incorrect file!") : 0;
	ft_lstrev(lst);
	return (len);
}

void		get_map(t_map *m, int width, int height)
{
	m->m_hei = height;
	m->m_wid = width;
	m->map = (int *)ft_my_malloc(sizeof(int) * width * height);
}

int			write_map(t_map *map, t_list *lst)
{
	t_write wr;

	wr.lst = lst;
	wr.y = -1;
	wr.s_count = 0;
	while (++wr.y < map->m_hei)
	{
		if (!(wr.s = ft_strsplit(wr.lst->content, ' ')))
			ft_error("Malloc failed");
		wr.x = -1;
		while (++wr.x < map->m_wid)
		{
			map->map[wr.y * map->m_wid + wr.x] = ft_atoi(wr.s[wr.x]);
			map->map[wr.y * map->m_wid + wr.x] > 22 ? \
			ft_error("map is failed") : 0;
			if (map->map[wr.y * map->m_wid + wr.x] >= 20 \
			&& map->map[wr.y * map->m_wid + wr.x] <= 22)
				wr.s_count++;
		}
		ft_2arrclean(&wr.s);
		wr.lst = wr.lst->next;
	}
	ft_cleanmem(&lst);
	return (wr.s_count);
}

void		write_sprites(t_map *m)
{
	int	x;
	int y;
	int spr_num;

	m->sprite = ft_my_malloc(sizeof(t_sprite *) * m->s_count);
	y = -1;
	spr_num = 0;
	while (++y < m->m_wid)
	{
		x = -1;
		while (++x < m->m_hei)
		{
			if (m->map[y * m->m_wid + x] >= 20 \
			&& m->map[y * m->m_wid + x] <= 22)
			{
				m->sprite[spr_num] = ft_my_malloc(sizeof(t_sprite) * 1);
				m->sprite[spr_num]->x = x == m->m_wid ? x - 0.5 : x + 0.5;
				m->sprite[spr_num]->y = y == m->m_wid ? y - 0.5 : x + 0.5;
				m->sprite[spr_num]->texture = m->map[y * m->m_wid + x];
				spr_num++;
			}
		}
	}
}
