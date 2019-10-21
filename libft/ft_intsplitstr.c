/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intsplitstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:45:17 by tjuana            #+#    #+#             */
/*   Updated: 2019/05/29 15:22:29 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	count(char const *str, char const *set)
{
	int		nb;

	nb = 0;
	while (*str)
	{
		while (in_set(set, *str))
			str++;
		if (*str)
			nb++;
		while (*str && !in_set(set, *str))
			str++;
	}
	return (nb);
}

int			*ft_intsplitstr(char const *str, char const *set)
{
	int		*tab;
	int		pos;
	int		i;

	if (!(tab = (int *)malloc(count(str, set) * sizeof(int))))
		return (NULL);
	pos = 0;
	i = 0;
	while (*str)
	{
		while (in_set(set, *str))
			str++;
		if (*str)
		{
			tab[pos++] = ft_atoi(str + i);
			while (*str && !in_set(set, *str))
				str++;
		}
	}
	return (tab);
}
