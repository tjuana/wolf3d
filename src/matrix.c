/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 16:38:34 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/02 19:15:33 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

///we need more optimizeted@!@@@@!!!@

t_matrix_4x4	ft_identify(t_matrix_4x4 neo)
{
	neo.i = -1;
	while (++neo.i < 4)
	{
		neo.j = -1;
		while (++neo.j < 4)
			neo.matrix[neo.i][neo.j] = 0;
	}
	neo.matrix[0][0] = 1.00;
	neo.matrix[1][1] = 1.00;
	neo.matrix[2][2] = 1.00;
	neo.matrix[3][3] = 1.00;
	return (neo);
}

t_matrix_4x4	ft_scale(t_matrix_4x4 neo, double scale)
{
	neo.matrix[0][0] = scale;
	neo.matrix[1][1] = scale;
	neo.matrix[2][2] = scale;
	neo.matrix[3][3] = 1.00;

	return (neo);
}

t_matrix_4x4	ft_translitation(t_matrix_4x4 neo, t_vector3 *vtc)
{
	neo.matrix[0][0] = 1.00;
	neo.matrix[1][1] = 1.00;
	neo.matrix[2][2] = 1.00;
	neo.matrix[3][3] = 1.00;
	neo.matrix[0][3] = vtc->x;
	neo.matrix[1][3] = vtc->y;
	neo.matrix[2][3] = vtc->z;
	return (neo);
}

t_matrix_4x4	ft_rx_matrix(t_matrix_4x4 neo, double angle)
{
	neo.matrix[0][0] = 1.00;
	neo.matrix[1][1] = cos(angle);
	neo.matrix[1][2] = -sin(angle);
	neo.matrix[2][1] = sin(angle);
	neo.matrix[2][2] = cos(angle);
	neo.matrix[3][3] = 1.00;
	return (neo);
}

t_matrix_4x4	ft_ry_matrix(t_matrix_4x4 neo, double angle)
{
	neo.matrix[0][0] = cos(angle);
	neo.matrix[0][2] = sin(angle);
	neo.matrix[1][1] = 1.00;
	neo.matrix[2][0] = -sin(angle);
	neo.matrix[2][2] = cos(angle);
	neo.matrix[3][3] = 1.00;
	return (neo);
}

t_matrix_4x4	ft_rz_matrix(t_matrix_4x4 neo, double angle)
{
	neo.matrix[0][0] = cos(angle);
	neo.matrix[0][1] = -sin(angle);
	neo.matrix[1][0] = sin(angle);
	neo.matrix[1][1] = cos(angle);
	neo.matrix[2][2] = 1.00;
	neo.matrix[3][3] = 1.00;
	return (neo);
}

t_matrix_4x4	ft_projection(t_matrix_4x4 neo, double ratio, \
double near, double far)
{
	neo.matrix[1][1] = 1 / tan(0.5 * DEG2RAD(FOV));
	neo.matrix[0][0] = neo.matrix[1][1] / ratio;
	neo.matrix[2][2] = -1 * (-near - far) / (near - far);
	neo.matrix[3][2] = -1.00;
	neo.matrix[2][3] = (2 * near * far) / (near - far);
	neo.matrix[3][3] = 0.00;
	return (neo);
}

t_matrix_4x4	ft_mult_matrix(t_matrix_4x4 this, t_matrix_4x4 rhs)
{
	t_matrix_4x4	reload;

	reload.i = -1;
	while (++reload.i < 4)
	{
		reload.j = -1;
		while (++reload.j < 4)
			reload.matrix[reload.i][reload.j] = 0;
	}
	reload.i = -1;
	while (++reload.i < 4)
	{
		reload.j = -1;
		while (++reload.j < 4)
		{
			reload.matrix[reload.i][reload.j] += this.matrix[reload.i][0] * rhs.matrix[0][reload.j];
			reload.matrix[reload.i][reload.j] += this.matrix[reload.i][1] * rhs.matrix[1][reload.j];
			reload.matrix[reload.i][reload.j] += this.matrix[reload.i][2] * rhs.matrix[2][reload.j];
			reload.matrix[reload.i][reload.j] += this.matrix[reload.i][3] * rhs.matrix[3][reload.j];
		}
	}
	return (reload);
}

t_matrix_4x4		ft_oppositive_matrix(t_matrix_4x4 neo)
{
	t_matrix_4x4	trinity;
	trinity.i = -1;
	while (++trinity.i < 4)
	{
		trinity.j = -1;
		while (++trinity.j < 4)
			trinity.matrix[trinity.i][trinity.j] = 0;
	}
	trinity.i = -1;
	while (++trinity.i < 4)
	{
		trinity.j = -1;
		while (++trinity.j < 4)
			trinity.matrix[trinity.i][trinity.j] = neo.matrix[trinity.j][trinity.i];
	}
	return (trinity);
}



t_vector3			ft_transform_vertex(t_vector3 this, t_matrix_4x4 neo)
{
	t_vector3	res;

	res.x = (this.x * neo.matrix[0][0]) + (this.y * neo.matrix[0][1]) + (this.z * neo.matrix[0][2]) + \
	(this.w * neo.matrix[0][3]);
	res.y = (this.x * neo.matrix[1][0]) + (this.y * neo.matrix[1][1]) + (this.z * neo.matrix[1][2]) + \
	(this.w * neo.matrix[1][3]);
	res.z = (this.x * neo.matrix[2][0]) + (this.y * neo.matrix[2][1]) + (this.z * neo.matrix[2][2]) + \
	(this.w * neo.matrix[2][3]);
	res.w = (this.x * neo.matrix[3][0]) + (this.y * neo.matrix[3][1]) + (this.z * neo.matrix[3][2]) + \
	(this.w * neo.matrix[3][3]);
	return (res);
}

t_vector3		ft_camera(t_vector3 vtx_orig, t_matrix_4x4 orient, t_vector3 world_vertex)
{
	t_vector3		vertex0;// need to define
	t_vector3		screen_vertex;
	t_vector3		oppv;
	t_matrix_4x4	trans;
	t_matrix_4x4	t_mult;
	t_matrix_4x4	t_proj;

	t_mult = ft_identify(t_mult);
	trans = ft_identify(trans);
	t_proj = ft_identify(t_proj);
	vertex0.x = 0;
	vertex0.y = 0;
	vertex0.z = 0;
	vertex0.w = 1;
	oppv = ft_vec3_create(&vtx_orig, &vertex0);
	trans = ft_translitation(trans, &oppv);
	orient = ft_oppositive_matrix(orient);
	t_mult = ft_mult_matrix(orient, trans);
	t_proj = ft_projection(t_proj, WIDTH / HIGHT, NEAR, FAR);

	screen_vertex = ft_transform_vertex(world_vertex, t_mult);
	screen_vertex = ft_transform_vertex(screen_vertex, t_proj);
	screen_vertex.x = (1 - screen_vertex.x) / (screen_vertex.z / 11.3) * WIDTH / 2;
	screen_vertex.y = (1 - screen_vertex.y) / (screen_vertex.z / 11.3) * HIGHT / 2;
	
	return (screen_vertex);
}
