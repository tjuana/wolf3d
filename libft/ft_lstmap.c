/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:13:38 by tjuana            #+#    #+#             */
/*   Updated: 2019/07/11 17:23:50 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *lst1;

	lst1 = f(ft_lstnew(lst->content, lst->content_size));
	if (lst)
	{
		lst1 = f(lst);
		lst1->next = ft_lstmap(lst->next, f);
		return (lst1);
	}
	return (NULL);
}
