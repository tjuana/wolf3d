/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:21:38 by tjuana            #+#    #+#             */
/*   Updated: 2019/04/07 17:22:47 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *ret;

	ret = (0);
	while (*s)
	{
		if (*s == c)
			ret = (char *)s;
		s++;
	}
	if (ret)
		return (ret);
	if (c == '\0')
		return ((char *)s);
	return (0);
}
