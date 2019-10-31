/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 13:02:04 by tjuana            #+#    #+#             */
/*   Updated: 2019/10/30 15:55:56 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*iter;
	int				delta;

	iter = b;
	delta = 0;
	while ((len = len - delta))
		if (len >= 8 && (delta = 8))
		{
			iter[len - 1] = c;
			iter[len - 2] = c;
			iter[len - 3] = c;
			iter[len - 4] = c;
			iter[len - 5] = c;
			iter[len - 6] = c;
			iter[len - 7] = c;
			iter[len - 8] = c;
		}
		else if (len >= 1 && (delta = 1))
			iter[len - 1] = c;
	return (b);
}
