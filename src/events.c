/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/02 15:09:18 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_handle_events(t_wolf3d *w)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		e.type == SDL_QUIT ? w->sdl->running = 0 : 0;
		if (e.type == SDL_KEYDOWN)
		{
			e.key.keysym.scancode == SDL_SCANCODE_ESCAPE ?
			w->sdl->running = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_W ? w->arr[0] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_S ? w->arr[1] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_A ? w->arr[2] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_D ? w->arr[3] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_SPACE ? w->arr[4] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_Q ? w->arr[5] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_R ? w->arr[6] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_F ? w->arr[7] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_T ? w->arr[8] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_G ? w->arr[9] = 1 : 0;
		}
		if (e.type == SDL_KEYUP)
		{
			e.key.keysym.scancode == SDL_SCANCODE_W ? w->arr[0] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_S ? w->arr[1] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_A ? w->arr[2] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_D ? w->arr[3] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_R ? w->arr[6] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_F ? w->arr[7] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_T ? w->arr[8] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_G ? w->arr[9] = 0 : 0;
		}
	}
}

static void		ft_left_rotation(t_wolf3d *w)
{
	t_matrix_4x4	rotation_matrix;

	// transform
	rotation_matrix = ft_identify(rotation_matrix);
	rotation_matrix = ft_rz_matrix(rotation_matrix, -T_CAM_Z_ANGLE);
	w->pl.camera_vector = ft_transform_vertex(w->pl.camera_vector, rotation_matrix);

	printf("%.2f\t%.2f\t%.2f\t%.2f\n", w->pl.camera_vector.x, w->pl.camera_vector.y, w->pl.camera_vector.z, w->pl.camera_vector.w);
}

static void		ft_right_rotation(t_wolf3d *w)
{
	t_matrix_4x4	rotation_matrix;

	// transform
	rotation_matrix = ft_identify(rotation_matrix);
	rotation_matrix = ft_rz_matrix(rotation_matrix, T_CAM_HR_ANGLE);
	w->pl.camera_vector = ft_transform_vertex(w->pl.camera_vector, rotation_matrix);

	printf("%.2f\t%.2f\t%.2f\t%.2f\n", w->pl.camera_vector.x, w->pl.camera_vector.y, w->pl.camera_vector.z, w->pl.camera_vector.w);
}

static void		ft_top_rotation(t_wolf3d *w)
{
	w->pl.cameraH += 0.02;
	if (w->pl.cameraH > 10.0)
		w->pl.cameraH = 10;
}

static void		ft_bottom_rotation(t_wolf3d *w)
{
	w->pl.cameraH -= 0.02;
	if (w->pl.cameraH < 1.0)
		w->pl.cameraH = 1;
}

static void		ft_top_camera_rotation(t_wolf3d *w)
{
	double			camera_tilt;
	t_matrix_4x4	rotation_matrix;

	camera_tilt = w->pl.camera_vector.z;
	camera_tilt += 0.01;
	if (camera_tilt > 0.5)
		camera_tilt = 0.5;

	w->pl.camera_vector.z = camera_tilt;
}

static void		ft_bottom_camera_rotation(t_wolf3d *w)
{
	double			camera_tilt;
	t_matrix_4x4	rotation_matrix;

	camera_tilt = w->pl.camera_vector.z;
	camera_tilt -= 0.01;
	if (camera_tilt < -0.5)
		camera_tilt = -0.5;

	w->pl.camera_vector.z = camera_tilt;
}

/*
**	ft_use_events(t_wolf3d *w) | debug
**	Function to...
*/

void			ft_use_events(t_wolf3d *w)
{
	if (w->arr[0] == 1)
	{
		w->sdl->i = 1;
		ft_load_sound(w);
		if (ft_step_forward_check(w, 1))
			w->pl.pos.x += w->pl.camera_vector.x * w->ms;
		if (ft_step_forward_check(w, 0))
			w->pl.pos.y += w->pl.camera_vector.y * w->ms;
	}
	if (w->arr[1] == 1)
	{
		if (ft_step_back_check(w, 1))
			w->pl.pos.x -= w->pl.camera_vector.x * w->ms;
		if (ft_step_back_check(w, 0))
			w->pl.pos.y -= w->pl.camera_vector.y * w->ms;
	}
	w->arr[2] == 1 ? ft_left_rotation(w) : 0;
	w->arr[3] == 1 ? ft_right_rotation(w) : 0;
	w->arr[4] == 1 ? ft_play_shot(w) : 0;
	w->arr[5] == 1 ? ft_play_music(w) : 0;

	// new functions for view transform
	w->arr[6] == 1 ? ft_top_rotation(w) : 0;
	w->arr[7] == 1 ? ft_bottom_rotation(w) : 0;
	w->arr[8] == 1 ? ft_top_camera_rotation(w) : 0;
	w->arr[9] == 1 ? ft_bottom_camera_rotation(w) : 0;
}
