/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:17:47 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/09 20:14:26 by dorange-         ###   ########.fr       */
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
}