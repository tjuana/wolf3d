/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:33:27 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/03 15:46:47 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	t_byte	*ptr_s1;
	t_byte	*ptr_s2;

	ptr_s1 = (t_byte*)s1;
	ptr_s2 = (t_byte*)s2;
	while (*ptr_s1 == *ptr_s2 && *ptr_s1 != '\0' && *ptr_s2 != '\0')
	{
		ptr_s1++;
		ptr_s2++;
	}
	return ((t_byte)(*ptr_s1) - (t_byte)(*ptr_s2));
}
