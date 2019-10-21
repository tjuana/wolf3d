/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:29:55 by tjuana            #+#    #+#             */
/*   Updated: 2019/04/20 19:12:31 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*p1;
	char	*p2;
	char	sw;

	if (!str || !(*str))
		return (str);
	p1 = str;
	p2 = str + ft_strlen(str) - 1;
	while (p2 > p1)
	{
		sw = *p1;
		*p1 = *p2;
		*p2 = sw;
		p1++;
		p2--;
	}
	return (str);
}
