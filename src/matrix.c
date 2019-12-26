/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 16:38:34 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/26 16:14:28 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "wolf3d.h"
#include <stdlib.h>
#include <math.h>

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
	// neo->i = -1;
	//вопрос в том что там мусор либо для всех матриц 
	//сначала делать identify иначе там мусор
	// while (++neo->i < 4)
	// {
	// 	neo->j = -1;
	// 	while (++neo->j < 4)
	// 		neo->matrix[neo->i][neo->j] = 0;
	// }
	neo.matrix[0][0] = scale;
	neo.matrix[1][1] = scale;
	neo.matrix[2][2] = scale;
	neo.matrix[3][3] = 1.00;

	return (neo);
}

t_matrix_4x4	ft_translitation(t_matrix_4x4 neo,t_vector3 *vtc)
{
	// neo.i = -1;
		//вопрос в том что там мусор либо для всех матриц 
	//сначала делать identify
	// while (++neo.i < 4)
	// {
	// 	neo.j = -1;
	// 	while (++neo.j < 4)
	// 		neo.matrix[neo.i][neo.j] = 0;
	// }
	neo.matrix[0][0] = 1.00;
	neo.matrix[1][1] = 1.00;
	neo.matrix[2][2] = 1.00;
	neo.matrix[3][3] = 1.00;
	neo.matrix[0][3] = vtc->x;
	neo.matrix[1][3] = vtc->y;
	neo.matrix[2][3] = vtc->z;
	return (neo);
}

int	main(void)
{
	t_matrix_4x4	ident;
	t_matrix_4x4	TRANS;
	t_matrix_4x4	scale;
	t_matrix_4x4	RX;
	t_vector3		vtx;

	vtx.x = 20.0;
	vtx.y = 20.0;
	vtx.z = 0;

	vtx = ft_vec3_create(NULL, &vtx);

	ident = ft_identify(ident);
	RX = ft_identify(RX);
	scale = ft_identify(scale);
	TRANS = ft_identify(TRANS);

	TRANS = ft_translitation(TRANS, &vtx);

	scale = ft_scale(scale, 10);

	RX = ft_RX_matrix(RX, angle)
	
	return (0);
}