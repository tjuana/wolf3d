/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:20:57 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/10 14:41:16 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	char *ft_parser_search_param(char *line, char *needly)
**
**	Function that search parameter and return a pointer for parameter.
** **************************************************************************
*/

char	*ft_parser_search_param(char *line, char *needly)
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

/*
** **************************************************************************
**	int ft_parser_get_param(char *line, char *needly)
**
**	Function that return parameter.
** **************************************************************************
*/

int		ft_parser_get_param(char *line, char *needly)
{
	char	*str;

	str = ft_parser_search_param(line, needly);
	if (str == NULL)
		ft_error("MAP INCORRECT");
	return (ft_atoi(str));
}
