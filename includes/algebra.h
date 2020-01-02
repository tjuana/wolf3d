/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:22:19 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/31 19:02:42 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGEBRA_H
# define ALGEBRA_H

# include "wolf3d.h"
# define DEG2RAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)
# define RAD2DEG(angleRadians) ((angleRadians) * 180.0 / M_PI)
// # define FOV (double)60.0
// # define WIDTH (double)640.0
// # define HIGHT (double)480.0
// # define NEAR (double)1.0
// # define FAR (double)100.0

# define FOV (double)90.0
# define WIDTH (double)WIN_WIDTH
# define HIGHT (double)WIN_HEIGHT
# define NEAR (double)1.0
# define FAR (double)100.0

// t_vector3 == vertex (?)
typedef struct  s_vector3
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vector3;

typedef struct	s_matrix_4x4
{
	double		matrix[4][4];
	int			i;
	int			j;
}				t_matrix_4x4;

t_vector3		ft_vec3_create(t_vector3 *orig, t_vector3 *dest);
double			ft_vec3_magnitude(t_vector3 this);
t_vector3		ft_vec3_add(t_vector3 this, t_vector3 rhs);
t_vector3		ft_vec3_sub(t_vector3 this, t_vector3 rhs);
t_vector3		ft_vec3_cross_product(t_vector3 this, t_vector3 rhs);
double			ft_vec3_dot_product(t_vector3 this, t_vector3 rhs);
double			ft_vec3_cosinus(t_vector3 this, t_vector3 rhs);
t_vector3		ft_vec3_opposite(t_vector3 this);
t_vector3		ft_vec3_scalar_product(t_vector3 this, double k);
t_vector3		ft_vec3_normalize(t_vector3 vtc);

// matrix transform
t_matrix_4x4	ft_identify(t_matrix_4x4 neo);
t_matrix_4x4	ft_scale(t_matrix_4x4 neo, double scale);
t_matrix_4x4	ft_translitation(t_matrix_4x4 neo, t_vector3 *vtc);
t_matrix_4x4	ft_rx_matrix(t_matrix_4x4 neo, double angle);
t_matrix_4x4	ft_ry_matrix(t_matrix_4x4 neo, double angle);
t_matrix_4x4	ft_rz_matrix(t_matrix_4x4 neo, double angle);
t_matrix_4x4	ft_projection(t_matrix_4x4 neo, double ratio, \
					double near, double far);
t_matrix_4x4	ft_mult_matrix(t_matrix_4x4 this, t_matrix_4x4 rhs);
t_matrix_4x4	ft_oppositive_matrix(t_matrix_4x4 neo);
t_vector3		ft_transform_vertex(t_vector3 this, t_matrix_4x4 neo);
t_vector3		ft_camera(t_vector3 vtx_orig, t_matrix_4x4 orient, t_vector3 world_vertex);

#endif
