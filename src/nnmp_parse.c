/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nnmp_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:21:54 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/09 20:29:21 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	*ft_parsing_search_param(char *line, char *needly)
{
	char	*str;

	str = ft_strstr(line, needly);
	if (str == NULL)
		return (NULL);
	str = ft_strchr(str, ':');
	str++;
	if (*str == '\0')
		return (NULL);
	return (str);
}

int		ft_parsing_get_param(char *line, char *needly)
{
	char	*str;

	str = ft_parsing_search_param(line, needly);
	if (str == NULL)
		ft_error("MAP INCORRECT");
	return (ft_atoi(str));
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
	ptr = ft_strchr(str, '[');
	if (ptr == NULL)
		ft_error("MAP INCORRENT");
	while (ptr != NULL && *ptr != '\0')
	{
		count[0]++;

		ptr++;
		ptr = ft_strchr(ptr, ',');
		if (ptr == NULL)
			ft_error("MAP INCORRENT");
		if (*ptr == ',')
			count[1]++;

		ptr++;
		ptr = ft_strchr(ptr, ']');
		if (ptr == NULL)
			ft_error("MAP INCORRENT");
		if (*ptr == ']')
			count[2]++;

		ptr++;
		ptr = ft_strchr(ptr, '[');
	}

	if (count[0] != count[1] ||
		count[1] != count[2] ||
		count[2] != count[0])
		return (-1);
	return (count[0]);
}

t_vector3		ft_parse_get_vertex(char **ptr, char *ptr_finish)
{
	int			i;
	double		coord[4];
	char		*ptr_comma;

	ft_bzero(coord, sizeof(int) * 4);
	if ((*ptr) == ptr_finish)
		return ((t_vector3){0.0, 0.0, 0.0, 0.0});
	i = 0;
	coord[i++] = (double)ft_atoi(*ptr);
	ptr_comma = ft_strchr((*ptr), ',');
	while (ptr_comma != NULL && ptr_comma++ < ptr_finish && *ptr_comma != '\0')
	{
		(*ptr) = ptr_comma + sizeof(char);
		coord[i++] = (double)ft_atoi(*ptr);
		ptr_comma = ft_strchr((*ptr), ',');
	}
	return ((t_vector3){coord[0], coord[1], coord[2], coord[3]});
}

t_vector3		*ft_parse_vertex(char **ptr)
{
	t_vector3	*p;
	char		*ptr_finish;

	p = malloc(sizeof(t_vector3));
	ft_bzero(p, sizeof(t_vector3));
	(*ptr) = ft_strchr((*ptr), '[');
	if ((*ptr) == NULL)
		ft_error("MAP INCORRENT");
	(*ptr)++;
	ptr_finish = ft_strchr((*ptr), ']');
	if (ptr_finish == NULL)
		ft_error("MAP INCORRENT");
	ptr_finish++;
	*p = ft_parse_get_vertex(ptr, ptr_finish);
	return (p);
}

void	ft_parsing_file_nnmp_sector_neighborhood(t_wolf3d *w, char **line, t_sector *sector)
{
	int			*neighborhood;
	char		*str;
	int			i;

	neighborhood = malloc(sizeof(void*) * sector->vertex_count);
	str = ft_parsing_search_param(*line, "neighborhood:");
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

void	ft_parsing_file_nnmp_sector_vertexes(t_wolf3d *w, char **line, t_sector *sector)
{
	t_vector3		**vertex;
	int				count;
	unsigned int	i;
	char			*ptr;

	ptr = ft_parsing_search_param(*line, " vertex:");
	count = ft_get_vertexes_count(*line);
	if (count < 3)
		ft_error("MAP INCORRECT");
	vertex = malloc(sizeof(void*) * count);
	i = 0;
	while (i < count)
	{
		vertex[i] = ft_parse_vertex(&ptr);
		i++;
	}
	sector->vertex = vertex;
	sector->vertex_count = count;
}

void	ft_parsing_file_nnmp_sector_param(t_wolf3d *w, char **line, t_sector *sector)
{
	sector->id = ft_parsing_get_param(*line, "sector:");
	sector->floor = (double)ft_parsing_get_param(*line, " f:");
	sector->height = (double)ft_parsing_get_param(*line, " h:");
	sector->txtr_floor = ft_parsing_get_param(*line, " txtr_floor:");
	sector->txtr_walls = ft_parsing_get_param(*line, " txtr_walls:");
	sector->txtr_ceil = ft_parsing_get_param(*line, " txtr_ceil:");
}

void		ft_parsing_file_nnmp_sector(t_wolf3d *w, char **line)
{
	t_sector	*sector;
	t_list		*list_item;

	sector = ft_my_malloc(sizeof(t_sector));

	ft_parsing_file_nnmp_sector_param(w, line, sector);
	ft_parsing_file_nnmp_sector_vertexes(w, line, sector);
	ft_parsing_file_nnmp_sector_neighborhood(w, line, sector);

	list_item = ft_lstnew(sector, sizeof(t_sector));
	if (w->sector == NULL)
		w->sector = list_item;
	else
		ft_lstadd(&(w->sector), list_item);
}

void	ft_parsing_file_nnmp_player(t_wolf3d *w, char **line)
{
	t_vector3		*vertex;
	int				count;
	char			*ptr;

	ptr = ft_parsing_search_param(*line, " vertex:");
	vertex = ft_parse_vertex(&ptr);
	w->pl.pos = (t_vector3){vertex->x, vertex->y, vertex->z, vertex->w};
	w->pl.cameraH = vertex->z;
	free(vertex);

	ptr = ft_parsing_search_param(*line, " camera:");
	vertex = ft_parse_vertex(&ptr);
	w->pl.camera_vector = (t_vector3){vertex->x, vertex->y, vertex->z, vertex->w};
	free(vertex);
}

void	ft_parsing_file_nnmp_sprite(t_wolf3d *w, char **line)
{
	return ;
}

void	ft_parsing_file_nnmp_enemy(t_wolf3d *w, char **line)
{
	return ;
}

/*
	void ft_parsing_file_nmp(int fd, t_wolf3d *w)

	Function that parsing the file in .nnmp format.
*/
void		ft_parsing_file_nnmp(int fd, t_wolf3d *w)
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
			ft_parsing_file_nnmp_sector(w, &line);
		else if (!ft_strncmp(line, "player", 6))
			ft_parsing_file_nnmp_player(w, &line);
		else if (!ft_strncmp(line, "sprite", 6))
			ft_parsing_file_nnmp_sprite(w, &line);
		else if (!ft_strncmp(line, "enemy", 5))
			ft_parsing_file_nnmp_enemy(w, &line);
		else if (!ft_strncmp(line, "//", 2) || ft_strlen(line) == 0)
			continue ;
		else
			ft_error("MAP INCORRECT");
		free(line);
		i++;
	}
	free(line);
}