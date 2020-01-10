/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nnmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:13:36 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/10 14:29:51 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	void ft_parser_nnmp_player(t_wolf3d *w, char **line)
**
**	Function to parse player parameters.
** **************************************************************************
*/

void		ft_parser_nnmp_player(t_wolf3d *w, char **line)
{
	t_vector3		*vertex;
	int				count;
	char			*ptr;

	ptr = ft_parser_search_param(*line, " vertex:");
	vertex = ft_parser_nnmp_vertex(&ptr);
	w->pl.pos = (t_vector3){vertex->x, vertex->y, vertex->z, vertex->w};
	w->pl.cameraH = vertex->z;
	free(vertex);
	ptr = ft_parser_search_param(*line, " camera:");
	vertex = ft_parser_nnmp_vertex(&ptr);
	w->pl.camera_vector = (t_vector3){vertex->x, vertex->y, vertex->z, \
		vertex->w};
	free(vertex);
}

/*
** **************************************************************************
**	void ft_parser_nnmp_sprite(t_wolf3d *w, char **line)
**
**	Function to parse sprite parameters.
** **************************************************************************
*/

void		ft_parser_nnmp_sprite(t_wolf3d *w, char **line)
{
	return ;
}

/*
** **************************************************************************
**	void ft_parser_nnmp_enemy(t_wolf3d *w, char **line)
**
**	Function to parse enemy parameters.
** **************************************************************************
*/

void		ft_parser_nnmp_enemy(t_wolf3d *w, char **line)
{
	return ;
}

/*
** **************************************************************************
**	void ft_parser_nnmp(int fd, t_wolf3d *w)
**
**	Function that parser the file in .nnmp format.
** **************************************************************************
*/

void		ft_parser_nnmp(int fd, t_wolf3d *w)
{
	char	*line;
	int		res;
	char	**map;
	int		i;

	i = 0;
	w->sector = NULL;
	while ((res = get_next_line(fd, &line)) > 0)
	{
		if (!ft_strncmp(line, "sector", 6))
			ft_parser_nnmp_sector(w, &line);
		else if (!ft_strncmp(line, "player", 6))
			ft_parser_nnmp_player(w, &line);
		else if (!ft_strncmp(line, "sprite", 6))
			ft_parser_nnmp_sprite(w, &line);
		else if (!ft_strncmp(line, "enemy", 5))
			ft_parser_nnmp_enemy(w, &line);
		else if (!ft_strncmp(line, "//", 2) || ft_strlen(line) == 0)
			continue ;
		else
			ft_error("MAP INCORRECT");
		free(line);
		i++;
	}
	free(line);
}
