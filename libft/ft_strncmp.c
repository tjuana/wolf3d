/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:16:43 by tjuana            #+#    #+#             */
/*   Updated: 2019/04/05 15:20:25 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && n != 0)
	{
		i++;
		n--;
	}
	if (s1[i] == s2[i] || (n == 0 && *--s1 == *--s2))
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
