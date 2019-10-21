/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:59:36 by tjuana            #+#    #+#             */
/*   Updated: 2019/04/14 16:24:30 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	t_byte			*pd;
	const t_byte	*ps;

	pd = (t_byte *)dst;
	ps = (t_byte *)src;
	while (n--)
	{
		*pd = *ps;
		if (*ps == (t_byte)c)
			return ((void*)pd + 1);
		pd++;
		ps++;
	}
	return (NULL);
}
