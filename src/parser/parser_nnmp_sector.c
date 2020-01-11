/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nnmp_sector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:21:54 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/11 11:21:57 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	void ft_parser_nnmp_sector_neighborhood(t_wolf3d *w, char **line,
**		t_sector *sector)
**
**	Function that parse neighborhood sectors.
** **************************************************************************
*/

void	ft_parser_nnmp_sector_neighborhood(t_wolf3d *w, char **line, \
			t_sector *sector)
{
	int			*neighborhood;
	char		*str;
	int			i;

	neighborhood = malloc(sizeof(void*) * sector->vertex_count);
	str = ft_parser_search_param(*line, "neighborhood:");
	if (str == NULL)
		ft_error("MAP INCORRECT");
	i = 0;
	while (i < sector->vertex_count && str != NULL)
	{
		neighborhood[i] = ft_atoi(str);
		i++;
		str = ft_strchr(str, ',');
		if (str == NULL)
			break ;
		str++;
	}
	if (i < sector->vertex_count)
		ft_error("MAP INCORRECT");
}

/*
** **************************************************************************
**	void ft_parser_nnmp_sector_vertexes(t_wolf3d *w, char **line,
**		t_sector *sector)
**
**	Function that parse vertexes for sector.
** **************************************************************************
*/

void	ft_parser_nnmp_sector_vertexes(t_wolf3d *w, char **line, \
			t_sector *sector)
{
	t_vector3		**vertex;
	int				count;
	unsigned int	i;
	char			*ptr;

	ptr = ft_parser_search_param(*line, " vertex:");
	count = ft_parser_get_vertexes_count(*line);
	if (count < 3)
		ft_error("MAP INCORRECT");
	vertex = malloc(sizeof(void*) * count);
	i = 0;
	while (i < count)
	{
		vertex[i] = ft_parser_nnmp_vertex(&ptr);
		i++;
	}
	sector->vertex = vertex;
	sector->vertex_count = count;
}

/*
** **************************************************************************
**	void ft_parser_nnmp_sector_param(t_wolf3d *w, char **line,
**		t_sector *sector)
**
**	Function that parse special sector parameters.
** **************************************************************************
*/

void	ft_parser_nnmp_sector_param(t_wolf3d *w, char **line, \
			t_sector *sector)
{
	sector->id = ft_parser_get_param(*line, "sector:");
	sector->floor = (double)ft_parser_get_param(*line, " f:");
	sector->height = (double)ft_parser_get_param(*line, " h:");
	sector->txtr_floor = ft_parser_get_param(*line, " txtr_floor:");
	sector->txtr_walls = ft_parser_get_param(*line, " txtr_walls:");
	sector->txtr_ceil = ft_parser_get_param(*line, " txtr_ceil:");
	sector->status = 1;
}

/*
** **************************************************************************
**	void ft_parser_nnmp_sector(t_wolf3d *w, char **line)
**
**	Function that parse sector parameters.
** **************************************************************************
*/

void	ft_parser_nnmp_sector(t_wolf3d *w, char **line)
{
	t_sector	*sector;
	t_list		*list_item;

	sector = ft_my_malloc(sizeof(t_sector));
	ft_parser_nnmp_sector_param(w, line, sector);
	ft_parser_nnmp_sector_vertexes(w, line, sector);
	ft_parser_nnmp_sector_neighborhood(w, line, sector);
	list_item = ft_lstnew(sector, sizeof(t_sector));
	if (w->sector == NULL)
		w->sector = list_item;
	else
		ft_lstadd(&(w->sector), list_item);
}
