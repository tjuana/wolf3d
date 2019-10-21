/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:25:19 by tjuana            #+#    #+#             */
/*   Updated: 2019/04/20 18:08:31 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chars(int n)
{
	int c;

	c = (n < 0) ? 2 : 1;
	while (n && (n /= 10))
		c++;
	return (c);
}

char		*ft_itoa(int n)
{
	char	*r;
	int		i;
	int		sign;

	i = 0;
	if (!(r = ft_strnew(chars(n))))
		return (NULL);
	sign = (n < 0) ? 1 : 0;
	while (n)
	{
		r[i++] = ABS(n % 10) + '0';
		n /= 10;
	}
	if (sign)
		r[i++] = '-';
	if (*r == 0)
		*r = '0';
	return (ft_strrev(r));
}
