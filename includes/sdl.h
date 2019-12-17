/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:43:48 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/17 20:18:30 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

typedef struct			s_sdl
{
	int					running;
	SDL_Window			*win;
	SDL_Surface			*win_surface;
	SDL_Surface			*wall_surface;
	SDL_Renderer		*renderer;
	Uint32				*pixels;
	SDL_Texture			*text;
	SDL_Texture			*test;	//test png file
	SDL_Surface			**surfaces;
	SDL_AudioSpec		*wav_spect;
	Uint32				*wav_len;
	Uint8				**wav_buff;
	SDL_AudioDeviceID	*audio_device;
	unsigned char		i;
	int					img;
}						t_sdl;

typedef struct			s_time
{
	Uint32				time;
	Uint32				old_time;
	Uint32				frame_time;
	Uint32				sound_old_time;
	Uint32				sound_time;
	Uint32				change_of_time;
	Uint32				play_time;
	Uint32				sound_sum_time;
	unsigned char		flag;
}						t_time;