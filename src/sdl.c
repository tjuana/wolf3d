/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:40:14 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/10 19:28:44 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sdl		*sdl_init(t_sdl *sdl)
{
	sdl = ft_my_malloc(sizeof(t_sdl));
	sdl->pixels = ft_my_malloc((sizeof(Uint32) * WIN_WIDTH) * WIN_HEIGHT);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, \
		"Couldn't initialize SDL: %s", SDL_GetError());
		return (0);
	}
	if (SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, \
	0, &sdl->win, &sdl->renderer) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, \
		"Couldn't create window and renderer: %s", SDL_GetError());
		return (0);
	}
	if (!(sdl->text = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888\
	, SDL_TEXTUREACCESS_STREAMING, WIN_WIDTH, WIN_HEIGHT)))
		ft_error("SDL non textures");
	sdl->running = 1;
	return (sdl);
}

int			ft_init_anim(t_wolf3d *wolf)
{
	wolf->anim.start_am = 0;
	wolf->anim.frame = 0;
	wolf->anim.pframe.size = (t_vector3){512, 512, 0, 0};
	wolf->anim.pframe.cd = (t_vector3){0, 0, 0, 0};
	wolf->anim.place = (t_vector3){WIN_WIDTH / 2 - 512 / 2, WIN_HEIGHT - 512};
	wolf->anim.frames = 0;
	return (0);
}

void		ft_init_wolf(t_wolf3d *w)
{
	w->mouse_vertex = (t_vector3){0, 0, 0, 0};
	// fov и lp
	w->fov = 1.5708; // 90 градусов
	//w->fov = 3.00000;
	w->l_p = WIN_WIDTH / (2 * tan(w->fov / 2)); // Расстояние до воображаемой стены
	
	// w->pl.camera_vector.x = 0;
	// w->pl.camera_vector.y = 1;
	// w->pl.camera_vector.z = 0;
	// w->pl.camera_vector.w = 0;

	// w->pl.cameraH = 1; // Высота камеры
	// w->pl.camera_tilt = 0; // Смещение камеры
	// w->pl.pos.x = 1.5; // Позиция игрока
	// w->pl.pos.y = 1.5;
	w->hit = 0;
	w->x = -1;

	// transform
	// w->transform_angle = 0.02;
	w->ms = 0.02;
	w->rs = 0.02;
	w->c.crs = cos(w->rs);
	w->c.srs = sin(w->rs);
	w->c.mcrs = cos(-w->rs);
	w->c.msrs = sin(-w->rs);

	w->c.half_height = (WIN_HEIGHT >> 1);
	w->c.camera_x_cnst = 2 / (double)WIN_WIDTH;
	w->z_buffer = ft_my_malloc(sizeof(double) * WIN_WIDTH);
	//w->weapon_texture = ft_my_malloc(sizeof(SDL_Surface *));
	//w->map_texture = ft_my_malloc(sizeof(SDL_Surface));
	w->sdl->textures = ft_my_malloc(sizeof(SDL_Surface *) * TEXTURES_NUMBER);
	w->t.flag = 1;
	ft_we_need_more_init(w);
}

void		ft_we_need_more_init(t_wolf3d *w)
{
	w->t.time = 0;
	w->t.old_time = 0;
	w->t.sound_old_time = 0;
	w->t.play_time = 1000;
	w->t.sound_sum_time = 0;
	w->arr[0] = 0;
	w->arr[1] = 0;
	w->arr[2] = 0;
	w->arr[3] = 0;
	w->arr[4] = 0;
	w->arr[5] = 0;
	w->arr[6] = 0;
	w->arr[7] = 0;
	w->arr[8] = 0;
	w->arr[9] = 0;
}

void		ft_init_multi_wolf(t_threads_help *w, t_wolf3d *head)
{
	w->sdl = head->sdl;
	w->map.map = head->map.map;
	//w->map.sprite = head->map.sprite;
	//w->map.sprite_ord = head->map.sprite_ord;
	//w->map.spr_dst = head->map.spr_dst;
	w->pl.cameraH = head->pl.cameraH; // new
	// w->pl.camera_tilt = head->pl.camera_tilt; // new
	w->pl.camera_vector = head->pl.camera_vector; // new
	w->map.m_wid = head->map.m_wid;
	w->map.m_hei = head->map.m_wid;
	w->pl.pos.x = head->pl.pos.x;
	w->pl.pos.y = head->pl.pos.y;
	w->z_buffer = head->z_buffer;
	w->half_height = head->c.half_height;
	w->camera_x_cnst = head->c.camera_x_cnst;
	w->sector = head->sector;
	w->fov = head->fov;
	w->l_p = head->l_p;
}
