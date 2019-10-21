/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:56:44 by tjuana            #+#    #+#             */
/*   Updated: 2019/04/13 18:00:32 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	t_byte			*pd;
	const t_byte	*ps;

	pd = (t_byte *)dst;
	ps = (t_byte *)src;
	i = 0;
	if (ps < pd)
		while (++i <= len)
			pd[len - i] = ps[len - i];
	else
		ft_memcpy(pd, ps, len);
	return (dst);
}
