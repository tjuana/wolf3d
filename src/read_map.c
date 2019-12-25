/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:17:47 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/24 16:23:19 by drafe            ###   ########.fr       */
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
	ft_check_map(map);
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
	size_t	width;
	int		res;

	len = 0;
	width = 0;
	while ((res = get_next_line(fd, &line)) > 0)
	{
		width == (size_t)0 ? width = ft_countwords(line, ' ') : 0;
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
			map->map[wr.y * map->m_wid + wr.x] > 23 ? \
			ft_error("Map is failed") : 0;
			if (map->map[wr.y * map->m_wid + wr.x] >= 21 \
			&& map->map[wr.y * map->m_wid + wr.x] <= 23)
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
	while (++y < m->m_hei)
	{
		x = -1;
		while (++x < m->m_wid)
		{
			if (m->map[y * m->m_wid + x] >= 21 \
			&& m->map[y * m->m_wid + x] <= 23)
			{
				m->sprite[spr_num] = ft_my_malloc(sizeof(t_sprite) * 1);
				m->sprite[spr_num]->pos.x = x == m->m_wid ? x - 0.5 : x + 0.5;
				m->sprite[spr_num]->pos.y = y == m->m_hei ? y - 0.5 : y + 0.5;
				m->sprite[spr_num]->texture = m->map[y * m->m_wid + x];
				spr_num++;
			}
		}
	}
}
