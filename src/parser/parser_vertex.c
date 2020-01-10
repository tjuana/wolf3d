/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vertex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:19:28 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/10 15:01:20 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	int ft_parser_get_vertexes_count(char *str)
**
**	Function that parse string and return vertexes
**	count or -1 if map invalid.
** **************************************************************************
*/

int				ft_parser_get_vertexes_count(char *str)
{
	char		*ptr;
	int			count[2];

	ft_bzero(count, sizeof(int) * 2);
	ptr = ft_strchr(str, '[');
	if (ptr == NULL)
		ft_error("MAP INCORRENT");
	while (ptr != NULL && *ptr != '\0')
	{
		count[0]++;
		ptr++;
		ptr = ft_strchr(ptr, ']');
		if (ptr == NULL)
			ft_error("MAP INCORRENT");
		if (*ptr == ']')
			count[1]++;
		ptr++;
		ptr = ft_strchr(ptr, '[');
	}
	if (count[0] != count[1])
		return (-1);
	return (count[0]);
}

/*
** **************************************************************************
**	t_vector3 ft_parser_nnmp_get_vertex(char **ptr, char *ptr_finish)
**
**	Function that parse string to vector and return
**	vertex type (t_vector3){x, y, z, w}.
** **************************************************************************
*/

t_vector3		ft_parser_nnmp_get_vertex(char **ptr, char *ptr_finish)
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

/*
** **************************************************************************
**	t_vector3 *ft_parser_nnmp_vertex(char **ptr)
**
**	Function that return vertex pointer.
** **************************************************************************
*/

t_vector3		*ft_parser_nnmp_vertex(char **ptr)
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
	*p = ft_parser_nnmp_get_vertex(ptr, ptr_finish);
	return (p);
}
