/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:54:20 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/26 13:07:03 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_load_textures(t_wolf3d *w)
{
	w->weapon_texture = ft_sdl_load_bmp("Textures/pistol.bmp");
	w->map_texture = ft_sdl_load_bmp("Textures/Grey9.bmp");
	w->sdl->surfaces[0] = ft_sdl_load_bmp("Textures/Stone1.bmp");
	w->sdl->surfaces[1] = ft_sdl_load_bmp("Textures/Stone7.bmp");
	w->sdl->surfaces[2] = ft_sdl_load_bmp("Textures/Stone9.bmp");//Stone9
	w->sdl->surfaces[3] = ft_sdl_load_bmp("Textures/WALL72.bmp");
	w->sdl->surfaces[4] = ft_sdl_load_bmp("Textures/WALL32.bmp");
	w->sdl->surfaces[5] = ft_sdl_load_bmp("Textures/WALL78.bmp");
	w->sdl->surfaces[6] = ft_sdl_load_bmp("Textures/WALL85.bmp");
	w->sdl->surfaces[7] = ft_sdl_load_bmp("Textures/WALL90.bmp");
	//w->sdl->surfaces[8] = ft_surf_from_bmp("Textures/WALL2.bmp");
	w->sdl->surfaces[8] = ft_sdl_load_bmp("Textures/WALL62.bmp");
	w->sdl->surfaces[9] = ft_sdl_load_bmp("Textures/WALL4.bmp");
	w->sdl->surfaces[10] = ft_sdl_load_bmp("Textures/WALL46.bmp");
	w->sdl->surfaces[11] = ft_sdl_load_bmp("Textures/Grey11.bmp");
	w->sdl->surfaces[12] = ft_sdl_load_bmp("Textures/WALL6.bmp");
	w->sdl->surfaces[13] = ft_sdl_load_bmp("Textures/WALL52.bmp");
	w->sdl->surfaces[14] = ft_sdl_load_bmp("Textures/WALL44.bmp");
	w->sdl->surfaces[15] = ft_sdl_load_bmp("Textures/wood.bmp");
	w->sdl->surfaces[16] = ft_sdl_load_bmp("Textures/WALL98.bmp");//WALL98
	w->sdl->surfaces[17] = ft_sdl_load_bmp("Textures/Wood1.bmp");
	w->sdl->surfaces[18] = ft_sdl_load_bmp("Textures/WALL90.bmp");
	w->sdl->surfaces[19] = ft_sdl_load_bmp("Textures/WALL54.bmp");
	w->sdl->surfaces[20] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->surfaces[21] = ft_sdl_load_bmp("Textures/pillar.bmp");
	w->sdl->surfaces[22] = ft_sdl_load_bmp("Textures/barrel.bmp");
}
