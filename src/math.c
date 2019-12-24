/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 13:44:37 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/24 21:01:35 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (this);
}

double			ft_vec3_magnitude(t_vector3 this)
{
	return ((double)(sqrt(pow(this.x, 2) + pow(this.y, 2) + pow(this.z, 2))));
}
    // public function add(Vector $rhs) {
    //     $v1 = new Vertex(array('x' => $this->_x + $rhs->getX(), 'y' => $this->_y + $rhs->getY(), 'z' => $this->_z + $rhs->getZ()));
    //     return (new Vector(array('dest' => $v1)));
    // }

t_vector3			ft_vec3_add(t_vector3 this, t_vector3 rhs)
{
	t_vector3	res;

	res.x = this.x + rhs.x;
	res.y = this.y + rhs.y;
	res.z = this.z + rhs.z;
	return (res);
}
t_vector3		ft_vec3_normalize(t_vector3 *orig, t_vector3 *dest)
{
	t_vector3	this;
	t_vector3	v0;
	t_vector3	v1;
	t_vector3	res;

	if (ft_vec3_magnitude(this) == 1)
	{
		res = ft_vec3_create(orig, dest);
		return (res);
	}
	else
	{
		v0.x = 0;
		v0.y = 0;
		v0.z = 0;
		v1.x = this.x / ft_vec3_magnitude(this);
		v1.y = this.y / ft_vec3_magnitude(this);
		v1.z = this.z / ft_vec3_magnitude(this);
		res = ft_vec3_create(&v0, &v1);
		return (res);
	}
}

int				main(void)
{
	t_vector3	vtx0;
	t_vector3	vtxX;
	t_vector3	vtxY;
	t_vector3	vtxZ;
	t_vector3	vtcXunit;
	t_vector3	vtcYunit;
	t_vector3	vtcZunit;
	t_vector3	dest1;
	t_vector3	vtc1;
	t_vector3	orig2;
	t_vector3	dest2;
	t_vector3	vtc2;
	t_vector3	nvtc2;
	

	vtx0.x = 0;
	vtx0.y = 0;
	vtx0.z = 0;
	vtx0.w = 0;
	
	vtxX.x = 1;
	vtxX.y = 0;
	vtxX.z = 0;
	vtxX.w = 0;
	
	vtxY.x = 0;
	vtxY.y = 1;
	vtxY.z = 0;
	vtxY.w = 0;
	
	vtxZ.x = 0;
	vtxZ.y = 0;
	vtxZ.z = 1;
	vtxZ.w = 0;

	dest1.x = -12.34;
	dest1.y = 23.45;
	dest1.z = -34.56;

	dest2.x = -12.34;
	dest2.y = 23.45;
	dest2.z = -34.56;

	orig2.x = 23.87;
	orig2.y = -37.95;
	orig2.z = 78.34;

	
	
	vtcXunit = ft_vec3_create(&vtx0, &vtxX);
	vtcYunit = ft_vec3_create(&vtx0, &vtxY);
	vtcZunit = ft_vec3_create(&vtx0, &vtxZ);
	
	vtc1 = ft_vec3_create(NULL, &dest1);
	vtc2 = ft_vec3_create(&orig2, &dest2);
	
	double magnito;

	magnito = ft_vec3_magnitude(vtc2);

	nvtc2 = ft_vec3_normalize(v)

	return (0);
}
