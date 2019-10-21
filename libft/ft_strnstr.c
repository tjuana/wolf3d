/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:01:05 by tjuana            #+#    #+#             */
/*   Updated: 2019/04/08 15:27:46 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t l)
{
	unsigned int i;
	unsigned int f;

	i = 0;
	f = 0;
	if (n[0] == '\0')
		return ((char*)h);
	while (h[i] != '\0' && (size_t)i < l)
	{
		f = 0;
		while (h[i + f] != '\0' && h[i + f] == n[f] && (size_t)(i + f) < l)
		{
			if (n[f + 1] == '\0')
				return ((char*)&h[i]);
			f++;
		}
		i++;
	}
	return (0);
}
