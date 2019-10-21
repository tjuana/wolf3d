/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:01:05 by tjuana            #+#    #+#             */
/*   Updated: 2019/04/20 18:21:24 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *hey, const char *ne)
{
	int is;
	int itf;

	is = 0;
	itf = 0;
	if (*ne == '\0')
		return ((char*)hey);
	while (*(hey + is) != '\0')
	{
		itf = 0;
		while (*(hey + is + itf) != '\0' && *(hey + is + itf) == *(ne + itf))
		{
			if (*(ne + itf + 1) == '\0')
				return ((char*)hey + is);
			itf++;
		}
		is++;
	}
	return (0);
}
