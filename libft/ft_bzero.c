/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:56:10 by tjuana            #+#    #+#             */
/*   Updated: 2019/10/30 16:34:51 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	int delta;

	delta = 1;
	while (n)
	{
		if (n >= 16)
		{
			*(__uint128_t *)s = 0;
			delta = 16;
		}
		else if (n >= 1)
		{
			*(char *)s = 0;
			delta = 1;
		}
		n = n - delta;
		s = ((char *)s) + delta;
	}
}
