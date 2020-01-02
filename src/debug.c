/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:49:37 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/02 17:01:33 by dorange-         ###   ########.fr       */
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
