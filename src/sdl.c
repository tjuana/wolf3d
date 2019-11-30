/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:40:14 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/29 16:13:16 by dorange-         ###   ########.fr       */
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
	wolf->anim.pframe.size = (t_coord){512, 512};
	wolf->anim.pframe.cd = (t_coord){0, 0};
	wolf->anim.place = (t_coord){WIN_WIDTH / 2 - 512 / 2, WIN_HEIGHT - 512};
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
	w->ms = 0.027;
	w->rs = 0.027;
	w->c.crs = cos(w->rs);
	w->c.srs = sin(w->rs);
	w->c.mcrs = cos(-w->rs);
	w->c.msrs = sin(-w->rs);
	w->c.half_height = (WIN_HEIGHT >> 1);
	w->c.camera_x_cnst = 2 / (double)WIN_WIDTH;
	w->z_buffer = ft_my_malloc(sizeof(double) * WIN_WIDTH);
	w->sdl->surfaces = ft_my_malloc(sizeof(SDL_Surface *) * TEXTURES_NUMBER);
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
	w->draw_end = 0;
	w->draw_start = 0;
	w->mouse_offset = 0;
	while (++i < KEYS_NBR)
		w->arr[i] = '0';
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
	w->pl.plane.y = head->pl.plane.y;
	w->camera_x_cnst = head->c.camera_x_cnst;
	w->mouse_offset = head->mouse_offset;
}
