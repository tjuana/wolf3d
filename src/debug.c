/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:49:37 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/10 20:22:57 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void	ft_debug_matrix(t_matrix_4x4 matrix)
{
	printf("( %6.2f %6.2f %6.2f %6.2f\n", matrix.matrix[0][0], matrix.matrix[0][1], matrix.matrix[0][2], matrix.matrix[0][3]);
	printf("  %6.2f %6.2f %6.2f %6.2f\n", matrix.matrix[1][0], matrix.matrix[1][1], matrix.matrix[1][2], matrix.matrix[1][3]);
	printf("  %6.2f %6.2f %6.2f %6.2f\n", matrix.matrix[2][0], matrix.matrix[2][1], matrix.matrix[2][2], matrix.matrix[2][3]);
	printf("  %6.2f %6.2f %6.2f %6.2f  )\n", matrix.matrix[3][0], matrix.matrix[3][1], matrix.matrix[3][2], matrix.matrix[3][3]);
}

/*
	void ft_print_sectors(t_list *ptr_list)
	
	Function that print the map sectors.
*/
void	ft_print_sectors(t_list *ptr_list)
{
	t_sector	*ptr_sector;
	int			i;
	int			j;

	i = 0;
	while (ptr_list != NULL)
	{
		// Get sector values
		ptr_sector = (t_sector*)ptr_list->content;

		j = 0;
		while (j < ptr_sector->vertex_count)
		{
			// Print the vertexes of sector
			printf(
				"SECTOR #%.2d\tVERTEX #%.2d\tx: %6.2f\ty: %6.2f\n",
				i,
				j,
				ptr_sector->vertex[j]->x,
				ptr_sector->vertex[j]->y
			);
			j++;
		}

		// Get next sector
		ptr_list = ptr_list->next;
		i++;
	}
}