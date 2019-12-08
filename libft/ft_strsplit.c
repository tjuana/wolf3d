/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:20:21 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/04 14:37:57 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_n_words(const char *s, char c)
{
	int		count;
	int		flag;

	flag = 0;
	count = 0;
	while (*s != '\0')
	{
		if (flag == 1 && *s == c)
			flag = 0;
		if (flag == 0 && *s != c)
		{
			flag = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int		ft_wlen(const char *s, char c)
{
	int		len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

static int		ft_strsplit_cleanup(char ***dst)
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

char			**ft_strsplit(char const *s, char c)
{
	char	**dst;
	int		nb_word;
	int		index;

	index = 0;
	if (s == NULL)
		return (NULL);
	nb_word = ft_n_words((const char *)s, c);
	dst = (char **)malloc(sizeof(*dst) * (ft_n_words((const char *)s, c) + 1));
	if (dst == NULL)
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s != '\0')
			s++;
		dst[index] = ft_strsub((const char *)s, 0, ft_wlen((const char *)s, c));
		if ((dst[index] == NULL) && ft_strsplit_cleanup(&dst))
			return (NULL);
		s = s + ft_wlen(s, c);
		index++;
	}
	dst[index] = NULL;
	return (dst);
}
