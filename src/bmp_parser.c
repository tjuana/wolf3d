/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:10:50 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/22 20:55:46 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			ft_bmp()
{
	t_bmp_image		bmp_img;

	if (bmp_img.head.type != 0x4D42)
		ft_putstr_fd("Error! Unrecognized file format.\n", 2);
	if (bmp_img.head.bits_per_pixel == 32)// Check if the file has bit mask color information
	{
		if(bmp_img.head.size >= (sizeof(bmp_img.head) + sizeof(bmp_img.c_head)))
		{
			//read((char*)&bmp_img.c_head, sizeof(bmp_img.c_head));
			// Check if the pixel data is stored as BGRA and if the color space type is sRGB
			//ft_check_color_header(bmp_img.c_head);
		}
		else
			ft_putstr_fd("Warning! The file does not seem to contain bit mask information\n", 2);
    }
	if (bmp_img.head.height_px < 0)
		ft_putstr_fd("The program can treat only BMP images with the origin in the bottom left corner!\n", 2);
}

static SDL_Surface	*ft_load_bmp(char *str)
{
	SDL_Surface	*surf;
	char		*buff;
	char		*tmp;
	int			fd;
	size_t		bytes;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return(NULL);
	if (!(tmp = (char *)malloc(sizeof(char) * (BMP_R_BUFF + 1))))
		return (NULL);
	tmp[0] = '\0';
	if (!(buff = (char *)malloc(sizeof(char) * (BMP_R_BUFF + 1))))
		return (NULL);
	while ((bytes = read(fd, buff, BMP_R_BUFF)) > 0)
	{
		buff[bytes] = '\0';
		tmp = ft_strjoin(tmp, buff);
		free(buff);
		buff = NULL;
		if (!(buff = (char *)malloc(sizeof(char) * (BMP_R_BUFF + 1))))
			return (NULL);	
	}
	ft_bmp();
	//printf("tmp = %s\n", tmp);
	surf = (SDL_Surface*)tmp;
	//exit(1);
	return(surf);
}

SDL_Surface			*ft_surf_from_bmp(char *str)
{
	SDL_Surface	*surf;

	surf = ft_load_bmp(str);
	if (surf == NULL)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
	return (surf);
}

