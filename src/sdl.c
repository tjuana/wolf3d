/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:40:14 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/06 18:16:06 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sdl		*sdl_init(t_sdl *sdl)
{
	sdl = ft_my_malloc(sizeof(t_sdl));

	sdl->pixels = ft_my_malloc((sizeof(Uint32) * WIN_W) * WIN_H);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, \
		"Couldn't initialize SDL: %s", SDL_GetError());
		return (0);
	}
	IMG_Init(IMG_INIT_PNG) == 0 ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	sdl->win = SDL_CreateWindow("WOLF3D", 650, 650, WIN_W, WIN_H, 0);
	sdl->renderer = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
	if (!(sdl->text = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888\
	, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H)))
		ft_error("SDL non textures");
	sdl->running = 1;
	if (TTF_Init() != 0)
		ft_putstr("ft_sdl_error(w)\n");
	return (sdl);
}

int			ft_init_anim(t_wolf3d *wolf)
{
	wolf->anim.start_am = 0;
	wolf->anim.frame = 0;
	wolf->anim.pframe.size = (t_coord){512, 512};
	wolf->anim.pframe.cd = (t_coord){0, 0};
	wolf->anim.place = (t_coord){WIN_W / 2 - 512 / 2, WIN_H - 512};
	wolf->anim.frames = 0;
	return (0);
}

void		ft_init_wolf(t_wolf3d *w)
{
	w->pl.pos.x = 1.6;
	w->pl.pos.y = 1.6;
	w->pl.dir.x = -1;
	w->pl.dir.y = 0;
	w->pl.plane.x = 0;
	w->pl.plane.y = 0.9;
	w->hit = 0;
	w->x = -1;
	w->ms = 0.03;
	w->rs = 0.04;
	w->c.crs = cos(w->rs);
	w->c.srs = sin(w->rs);
	w->c.mcrs = cos(-w->rs);
	w->c.msrs = sin(-w->rs);
	w->c.half_height = (WIN_H >> 1);
	w->c.camera_x_cnst = 2 / (double)WIN_W;
	w->z_buffer = ft_my_malloc(sizeof(double) * WIN_W);
	w->sdl->surfaces = ft_my_malloc(sizeof(w->sdl->surfaces) * TEXTURES_NUMBER);
	w->t.flag = 1;
	ft_we_need_more_init(w);
}

void		ft_we_need_more_init(t_wolf3d *w)
{
	int		i;

	i = -1;
	w->t.time = 0;
	w->t.old_time = 0;
	w->t.sound_old_time = 0;
	w->t.play_time = 1000;
	w->t.sound_sum_time = 0;
	w->draw_end = 0;//w->c.half_height;
	w->draw_start = 0;
	w->mouse_offset = 0;//look up & down
	w->pl.st.life = 100;
	w->pl.st.ammo = 40;
	while (++i < w->map.s_count)
	{
		w->map.sprite[i]->go = 0;
		w->map.sprite[i]->dir.x = 1;
		w->map.sprite[i]->dir.y = 1;
		w->map.sprite[i]->dist = -10;
	}
	i = -1;
	ft_door_create(w);
	while (++i < KEYS_NBR - 1)
		w->arr[i] = 0;
	w->pl.menu = 1;
	w->sdl->font.half_menu = 0;
	w->lol = 0;
	ft_menu_back(w);
	//SDL_WarpMouseInWindow(w->sdl->win, 650, 650);
}

void		ft_init_multi_wolf(t_threads_help *w, t_wolf3d *head)
{
	w->sdl = head->sdl;
	w->map.map = head->map.map;
	w->map.m_wid = head->map.m_wid;
	w->map.m_hei = head->map.m_wid;
	w->pl.pos.x = head->pl.pos.x;
	w->pl.pos.y = head->pl.pos.y;
	w->pl.dir.x = head->pl.dir.x;
	w->pl.dir.y = head->pl.dir.y;
	w->pl.plane.x = head->pl.plane.x;
	w->z_buffer = head->z_buffer;
	w->half_height = head->c.half_height;
	w->mouse_offset = head->mouse_offset;
	w->camera_x_cnst = head->c.camera_x_cnst;
	w->pl.plane.y = head->pl.plane.y;
	w->map.sprite = head->map.sprite;
	w->map.s_dst = head->map.s_dst;
	w->map.s_ord = head->map.s_ord;
}
