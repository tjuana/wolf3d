/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:08:31 by tjuana            #+#    #+#             */
/*   Updated: 2019/05/04 16:29:00 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t len)
{
	char	*copy;
	size_t	l;

	l = ft_strnlen(s1, len);
	if (!(copy = (char *)malloc(len + 1)))
		return (NULL);
	copy[len] = '\0';
	return ((char *)ft_memcpy(copy, s1, len));
}
