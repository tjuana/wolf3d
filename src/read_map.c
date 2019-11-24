/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:17:47 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/19 15:27:12 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
