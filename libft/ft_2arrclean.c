/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2arrclean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:16:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/11 13:41:06 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_2arrclean(char ***dst)
{
	size_t i;

	i = 0;
	while ((*dst)[i])
	{
		free((*dst)[i]);
		(*dst)[i] = NULL;
		i++;
	}
	free(*dst);
	*dst = NULL;
	dst = NULL;
	return (1);
}
