/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 16:38:34 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/25 17:48:25 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_vector3		ft_vec3_create(t_vector3 *orig, t_vector3 *dest)
{
	t_vector3	this;
	t_vector3	orig2;

	if (orig == NULL)
	{
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

t_vector3		ft_vec3_add(t_vector3 this, t_vector3 rhs)
{
	t_vector3	res;

	res.x = this.x + rhs.x;
	res.y = this.y + rhs.y;
	res.z = this.z + rhs.z;
	res.w = 0;//вот тут хз чей коэф брать
	return (res);
}

t_vector3		ft_vec3_sub(t_vector3 this, t_vector3 rhs)
{
	t_vector3	res;

	res.x = this.x - rhs.x;
	res.y = this.y - rhs.y;
	res.z = this.z - rhs.z;
	res.w = 0;//вот тут хз чей коэф брать
	return (res);
}

t_vector3		ft_vec3_cross_product(t_vector3 this, t_vector3 rhs)
{
	t_vector3	res;

	res.x = this.y * rhs.z - this.z * rhs.y;
	res.y = this.z * rhs.x - this.x * rhs.z;
	res.z = this.x * rhs.y - this.y * rhs.x;
	res.w = 0;//вот тут хз чей коэф брать
	return (res);
}
