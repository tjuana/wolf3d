/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 13:44:37 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/25 16:43:17 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		ft_vec3_dot_product(t_vector3 this, t_vector3 rhs)
{
	double	res;

	res = this.x * rhs.x + this.y * rhs.y + this.z * rhs.z;
	return (res);
}

double		ft_vec3_cosinus(t_vector3 this, t_vector3 rhs)
{
	double	res;

	res = ft_vec3_dot_product(this, rhs) / (ft_vec3_magnitude(this) * \
	sqrt(pow(rhs.x, 2) + pow(rhs.y, 2) + pow(rhs.z, 2)));
	return (res);
}

t_vector3	ft_vec3_opposite(t_vector3 this)
{
	t_vector3	res;

	res.x = -this.x;
	res.y = -this.y;
	res.z = -this.z;
	res.w = this.w;//вот тут хз чей коэф брать
	return (res);
}

t_vector3	ft_vec3_scalar_product(t_vector3 this, double k)
{
	t_vector3	res;

	res.x = this.x * k;
	res.y = this.y * k;
	res.z = this.z * k;
	res.w = this.w;//вот тут хз чей коэф брать
	return (res);
}

t_vector3	ft_vec3_normalize(t_vector3 vtc)
{
	t_vector3	v0;
	t_vector3	v1;

	if (ft_vec3_magnitude(vtc) == 1)
		return (vtc);
	v0.x = 0;
	v0.y = 0;
	v0.z = 0;
	v1.x = vtc.x / ft_vec3_magnitude(vtc);
	v1.y = vtc.y / ft_vec3_magnitude(vtc);
	v1.z = vtc.z / ft_vec3_magnitude(vtc);
	return (ft_vec3_create(&v0, &v1));
}
