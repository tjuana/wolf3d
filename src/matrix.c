/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 16:38:34 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/26 18:51:13 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "wolf3d.h"
#include <stdlib.h>
# include <math.h>
# define DEG2RAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)
# define RAD2DEG(angleRadians) ((angleRadians) * 180.0 / M_PI)
#define FOV (double)60

typedef struct	s_vector3
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vector3;

t_vector3		ft_vec3_create(t_vector3 *orig, t_vector3 *dest)
{
	t_vector3	this;

	if (orig == NULL)
	{
		t_vector3	orig2;
		orig2.x = 0;
		orig2.y = 0;
		orig2.z = 0;
		orig2.w = 1;
		this.x = dest->x - orig2.x;
		this.y = dest->y - orig2.y;
		this.z = dest->z - orig2.z;
		return (this);
	}
	this.x = dest->x - orig->x;
	this.y = dest->y - orig->y;
	this.z = dest->z - orig->z;
	this.w = 0;
	return (this);
}

double			ft_vec3_magnitude(t_vector3 this)
{
	return ((double)(sqrt(pow(this.x, 2) + pow(this.y, 2) + pow(this.z, 2))));
}

t_vector3			ft_vec3_add(t_vector3 this, t_vector3 rhs)
{
	t_vector3	res;

	res.x = this.x + rhs.x;
	res.y = this.y + rhs.y;
	res.z = this.z + rhs.z;
	res.w = 0;//вот тут хз чей коэф брать
	return (res);
}

t_vector3			ft_vec3_sub(t_vector3 this, t_vector3 rhs)
{
	t_vector3	res;

	res.x = this.x - rhs.x;
	res.y = this.y - rhs.y;
	res.z = this.z - rhs.z;
	res.w = 0;//вот тут хз чей коэф брать
	return (res);
}

t_vector3			ft_vec3_cross_product(t_vector3 this, t_vector3 rhs)
{
	t_vector3	res;

	res.x = this.y * rhs.z - this.z * rhs.y;
	res.y = this.z * rhs.x - this.x * rhs.z;
	res.z = this.x * rhs.y - this.y * rhs.x
	;
	res.w = 0;//вот тут хз чей коэф брать
	return (res);
}

double			ft_vec3_dot_product(t_vector3 this, t_vector3 rhs)
{
	double	res;

	res = this.x * rhs.x + this.y * rhs.y + this.z * rhs.z;
	return (res);
}

double			ft_vec3_cosinus(t_vector3 this, t_vector3 rhs)
{
	double	res;

	res = ft_vec3_dot_product(this, rhs) / (ft_vec3_magnitude(this) * sqrt(pow(rhs.x, 2) + pow(rhs.y, 2) + pow(rhs.z, 2)));
	return (res);
}

t_vector3			ft_vec3_opposite(t_vector3 this)
{
	t_vector3	res;

	res.x = -this.x;
	res.y = -this.y;
	res.z = -this.z;
	res.w = 1;
	return (res);
}

t_vector3			ft_vec3_scalar_product(t_vector3 this, double k)
{
	t_vector3	res;

	res.x = this.x * k;
	res.y = this.y * k;
	res.z = this.z * k;
	res.w = 1;
	return (res);
}

t_vector3		ft_vec3_normalize(t_vector3 vtc)
{
	t_vector3	v0;
	t_vector3	v1;

	if (ft_vec3_magnitude(vtc) == 1)
		return (vtc);
	else
	{
		v0.x = 0;
		v0.y = 0;
		v0.z = 0;
		v1.x = vtc.x / ft_vec3_magnitude(vtc);
		v1.y = vtc.y / ft_vec3_magnitude(vtc);
		v1.z = vtc.z / ft_vec3_magnitude(vtc);
		return (ft_vec3_create(&v0, &v1));
	}
}

///we need more optimizeted@!@@@@!!!@

typedef struct	s_matrix_4x4
{
	double		matrix[4][4];
	int			i;
	int			j;
}				t_matrix_4x4;

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
	t_matrix_4x4 reload;

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

int	main(void)
{
	t_matrix_4x4	ident;
	t_matrix_4x4	trans;
	t_matrix_4x4	scale;
	t_matrix_4x4	RX;
	t_matrix_4x4	RY;
	t_matrix_4x4	RZ;
	t_matrix_4x4	proj;
	t_matrix_4x4	mult;
	t_vector3		vtx;
	double			angle;
	double			angle2;
	double			angle3;
	double			ratio;
	double			near;
	double			far;

	ratio = (double)640 / (double)480;
	near = 1.0;
	far = -50.0;

	angle = M_PI_4;
	angle2 = M_PI_2;
	angle3 = 2 * M_PI;

	vtx.x = 20.0;
	vtx.y = 20.0;
	vtx.z = 0;

	vtx = ft_vec3_create(NULL, &vtx);

	ident = ft_identify(ident);
	RX = ft_identify(RX);
	RY = ft_identify(RY);
	RZ = ft_identify(RZ);
	scale = ft_identify(scale);
	trans = ft_identify(trans);
	proj = ft_identify(proj);
	ident = ft_identify(mult);

	trans = ft_translitation(trans, &vtx);

	scale = ft_scale(scale, 10);

	RX = ft_rx_matrix(RX, angle);
	RY = ft_ry_matrix(RY, angle2);
	RZ = ft_rz_matrix(RZ, angle3);

	proj = ft_projection(proj, ratio, near, far);

	mult = ft_mult_matrix(ft_mult_matrix(ft_mult_matrix(trans, RX), RY), scale);
	
	return (0);
}