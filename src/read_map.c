/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:17:47 by tjuana            #+#    #+#             */
/*   Updated: 2019/10/25 14:36:33 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		read_file(int fd, t_map *map)
{
	t_list	*lst;
	int		str;

	lst = NULL;
	str = get_lines(fd, &lst);
	get_map(map, ft_countwords(lst->content, ' '), ft_lstcount(lst));
	
	map->s_count = write_map(map, lst);
	/*if (map->s_count)
	{
		write_sprites(map);
		map->s_ord = ft_my_malloc(sizeof(int) * map->s_count);
		map->s_dst = ft_my_malloc(sizeof(double) * map->s_count);
	}*/
}

int			get_lines(int fd, t_list **lst)
{
	t_list	*tmp;
	char	*line;
	int		str;
	int		height;
	int		width;
	int		res;

	str = 0;
	width = -1;
	while ((res = get_next_line(fd, &line)) > 0)
	{
		width == -1 ? width = ft_countwords(line, ' ') : 0;
		width != ft_countwords(line, ' ') ? ft_error("Error map") : 0;
		if (!(tmp = ft_lstnew(line, ft_strlen(line) + 1)))
			ft_error("MAlloc failed");
			ft_lstadd(lst, tmp);
			ft_strdel(&line);
			str++;
	}
	res < 0 ? ft_error("Incorrect file!") : 0;
	ft_lstrev(lst);
	return (str);	
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
			//printf("%d ", map->map[wr.y * map->m_wid + wr.x]);
			///change textures
			map->map[wr.y * map->m_wid + wr.x] > 22 ? ft_error("map is failed") : 0;
			if (map->map[wr.y * map->m_wid + wr.x] >= 20 && map->map[wr.y * map->m_wid + wr.x] <= 22)
				wr.s_count++;
		}
		//printf("\n");
		//clean 2d array
		wr.lst = wr.lst->next;
	}
	ft_cleanmem(&lst);
	return (wr.s_count);
}

//write sprites