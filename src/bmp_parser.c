/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:10:50 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/25 19:29:19 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	uint32_t ft_file_size(t_bmp_h	*head)
**	Function to get image size
** **************************************************************************
*/

static uint32_t			ft_img_size(t_bmp_h	*head)
{
	head->bits_per_pixel += 0;
	return (0);
}

/*
** **************************************************************************
**	uint32_t ft_file_size(char *str)
**	Function to get file size
** **************************************************************************
*/

static uint32_t			ft_file_size(char *str)
{
	str += 0;
	return (0);
}

/*
** **************************************************************************
**	void ft_check_header()
**	Function to check header.
**	A header is valid if:
**	1. its magic number is 0x4d42,
**	2. image data begins immediately after the header data
**	(header->offset == BMP HEADER SIZE),
**	3. the DIB header is the correct size (DIB_HEADER_SIZE),
**	4. there is only one image plane,
**	5. there is no compression (header->compression == 0),
**	6. num_colors and  important_colors are both 0,
**	7. the image has 24 bits per pixel,
**	8. the size and image_size_bytes fields are correct in relation to the bits,
**	width, and height fields and in relation to the file size.
** **************************************************************************
*/

static int			ft_check_header(t_bmp_h	*head, char *str)
{
	return 
		head->type == BMP_MAGIC_VALUE
        && head->offset == BMP_HEADER_SIZE
        && head->dib_header_size == BMP_DIB_HEADER_SIZE
        && head->num_planes == BMP_NUM_PLANE
        && head->compression == BMP_COMPRESSION
        && head->num_colors == BMP_NUM_COLORS && head->important_colors == BMP_IMPORTANT_COLORS
        && head->bits_per_pixel == BMP_BITS_PER_PIXEL
        && head->size == ft_file_size(str) && head->image_size_bytes == ft_img_size(head);
}

/*
** **************************************************************************
**	void ft_test_mv_l(t_wolf3d *w)
**	Function to parse bmp
** **************************************************************************
*/

static void			ft_bmp_parser(int fd, char *str)
{
	t_bmp_image		*bmp_img;
	unsigned int	buff[BMP_HEADER_SIZE + 1];
	size_t			bytes;
	int				i;

	i = 99;
	atoi(str);
	if (!(bmp_img = malloc(sizeof(bmp_img))))
		return ;
	bytes = read(fd, &bmp_img->head, sizeof(bmp_img->head));
	buff[bytes] = '\0';
	printf("bytes=%zu  bpp=%i", bytes, bmp_img->head.size);
	i = ft_check_header(&bmp_img->head, str);
	printf("bytes=%zu  bpp=%i	i=%i", bytes, bmp_img->head.size, i);
	if ((i == 0) || (bytes == 1))
		return ;
}

/*
** **************************************************************************
**	static SDL_Surface *ft_load_bmp(char *str)
**	Function to read from bmp file.
** **************************************************************************
*/

static SDL_Surface	*ft_load_bmp(char *str)
{
	SDL_Surface	*surf;
	//char		*buff;
	unsigned char	*buff;
	char		*tmp;
	int			fd;
	size_t		bytes;

	bytes = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return(NULL);
	if (!(tmp = (char *)malloc(sizeof(char) * (BMP_R_BUFF + 1))))
		return (NULL);
	tmp[0] = '\0';
	if (!(buff = (unsigned char *)malloc(sizeof(unsigned char) * (BMP_R_BUFF + 1))))
		return (NULL);
	/*read(fd, buff, BMP_R_BUFF);
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
	printf("tmp = \"%s\"\n", tmp);*/
	ft_bmp_parser(fd, str);
	surf = (SDL_Surface*)tmp;
	exit(1);
	return(surf);
}

/*
** **************************************************************************
**	SDL_Surface *ft_surf_from_bmp(char *str)
**	Function to create surface from bmp file.
** **************************************************************************
*/

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

