/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:11:29 by tjuana            #+#    #+#             */
/*   Updated: 2019/04/13 18:00:09 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	t_byte			*pd;
	const t_byte	*ps;

	if (src == dst)
		return (dst);
	pd = (t_byte *)dst;
	ps = (t_byte *)src;
	while (n--)
		*pd++ = *ps++;
	return (dst);
}
