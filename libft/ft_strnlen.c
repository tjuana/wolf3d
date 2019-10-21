/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:12:53 by tjuana            #+#    #+#             */
/*   Updated: 2019/05/04 15:32:13 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	char	*s1;
	size_t	len;

	len = 0;
	s1 = (char*)s;
	while (*s1 && len < maxlen)
	{
		s1++;
		len++;
	}
	return ((size_t)(s1 - s));
}
