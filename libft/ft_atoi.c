/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:28:30 by tjuana            #+#    #+#             */
/*   Updated: 2019/04/20 18:11:17 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
{
	unsigned long long	res;
	int					otr;

	otr = 1;
	res = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		otr = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= 0 && ft_isdigit(*str))
	{
		res = res * 10;
		res += ((*str++) - '0');
		if ((res * 10) < res)
			return (otr > 0) ? (-1) : (0);
	}
	return (res * otr);
}
