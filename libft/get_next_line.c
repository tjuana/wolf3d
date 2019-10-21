/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:10:22 by tjuana            #+#    #+#             */
/*   Updated: 2019/07/11 14:56:32 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

static t_gnl	*gnl_find_or_create(const int fd, t_list **my_list)
{
	t_list	*file;
	t_gnl	file_data;

	file = *my_list;
	while (file)
	{
		if (((t_gnl *)(file->content))->fd == fd)
			return (file->content);
		file = file->next;
	}
	file_data.fd = fd;
	if ((file_data.buff = ft_strnew(BUFF_SIZE)) == NULL)
		return (NULL);
	if ((file = ft_lstnew(&file_data, sizeof(file_data))) == NULL)
		return (NULL);
	ft_lstadd(my_list, file);
	return ((*my_list)->content);
}

static ssize_t	gnl_read_line(t_gnl *file)
{
	char		buff[BUFF_SIZE + 1];
	ssize_t		r;
	char		*temp;

	r = 1;
	while (ft_strstr(file->buff, "\n") == NULL && \
	(r = read(file->fd, &buff, BUFF_SIZE)) > 0)
	{
		buff[r] = '\0';
		temp = file->buff;
		file->buff = ft_strjoin(file->buff, buff);
		ft_strdel(&temp);
	}
	return (r);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*my_list;
	t_gnl			*file;
	ssize_t			r;
	char			*temp;
	int				endl;

	if (fd < 0 || !line)
		return (-1);
	file = gnl_find_or_create(fd, &my_list);
	if ((r = gnl_read_line(file)) == -1)
		return (-1);
	temp = file->buff;
	if ((endl = (ft_strchr(file->buff, '\n') > 0)))
		*line = ft_strsub(file->buff, 0, ft_strchr(file->buff, '\n') \
		- file->buff);
	else
		*line = ft_strdup(file->buff);
	file->buff = ft_strsub(file->buff, (unsigned int)(ft_strlen(*line) + endl),
			(size_t)(ft_strlen(file->buff) - (ft_strlen(*line) + endl)));
	ft_strdel(&temp);
	return (!(!(**line) && !r));
}
