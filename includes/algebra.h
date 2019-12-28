/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:22:19 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/28 17:05:35 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGEBRA_H
# define ALGEBRA_H

# include "wolf3d.h"
# define DEG2RAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)
# define RAD2DEG(angleRadians) ((angleRadians) * 180.0 / M_PI)
# define FOV (double)60
# define WIDTH (double)640
# define HIGHT (double)480
# define NEAR (double)1
# define FAR (double)100

typedef struct  s_vector3
{
    double      x;
    double      y;
    double      z;
    double      w;
}               t_vector3;

typedef struct	s_matrix_4x4
{
	double		matrix[4][4];
	int			i;
	int			j;
}				t_matrix_4x4;

#endif