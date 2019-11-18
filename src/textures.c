/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:54:20 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/14 12:32:06 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_load_textures(t_wolf3d *w)
{
	w->weapon_texture = ft_sdl_load_bmp("Textures/pistol.bmp");
	w->map_texture = ft_sdl_load_bmp("Textures/Grey9.bmp");
	w->sdl->textures[0] = ft_sdl_load_bmp("Textures/Stone1.bmp");
	w->sdl->textures[1] = ft_sdl_load_bmp("Textures/Stone7.bmp");
	w->sdl->textures[2] = ft_sdl_load_bmp("Textures/Stone9.bmp");
	w->sdl->textures[3] = ft_sdl_load_bmp("Textures/WALL24.bmp");
	w->sdl->textures[4] = ft_sdl_load_bmp("Textures/WALL32.bmp");
	w->sdl->textures[5] = ft_sdl_load_bmp("Textures/WALL34.bmp");
	w->sdl->textures[6] = ft_sdl_load_bmp("Textures/WALL52.bmp");
	w->sdl->textures[7] = ft_sdl_load_bmp("Textures/WALL90.bmp");
	w->sdl->textures[8] = ft_sdl_load_bmp("Textures/WALL2.bmp");
	w->sdl->textures[9] = ft_sdl_load_bmp("Textures/WALL4.bmp");
	w->sdl->textures[10] = ft_sdl_load_bmp("Textures/Grey9.bmp");
	w->sdl->textures[11] = ft_sdl_load_bmp("Textures/Grey11.bmp");
	w->sdl->textures[12] = ft_sdl_load_bmp("Textures/WALL6.bmp");
	w->sdl->textures[13] = ft_sdl_load_bmp("Textures/WALL52.bmp");
	w->sdl->textures[14] = ft_sdl_load_bmp("Textures/WALL44.bmp");
	w->sdl->textures[15] = ft_sdl_load_bmp("Textures/wood.bmp");
	w->sdl->textures[16] = ft_sdl_load_bmp("Textures/Wood1.bmp");
	w->sdl->textures[17] = ft_sdl_load_bmp("Textures/Wood100.bmp");
	w->sdl->textures[18] = ft_sdl_load_bmp("Textures/WALL90.bmp");
	w->sdl->textures[19] = ft_sdl_load_bmp("Textures/WALL68.bmp");
	w->sdl->textures[20] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[21] = ft_sdl_load_bmp("Textures/pillar.bmp");
	w->sdl->textures[22] = ft_sdl_load_bmp("Textures/barrel.bmp");
}
