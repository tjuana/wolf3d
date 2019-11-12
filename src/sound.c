/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:42:06 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/11 13:33:38 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_init_sound(t_wolf3d *w)
{
	w->sdl->wav_spect = ft_my_malloc(sizeof(SDL_AudioSpec) * 3);
	w->sdl->wav_buff = ft_my_malloc(sizeof(Uint8 *) * 3);
	w->sdl->wav_len = ft_my_malloc(sizeof(Uint32) * 3);
	w->sdl->audio_device = ft_my_malloc(sizeof(SDL_AudioDeviceID) * 3);
	
	SDL_LoadWAV("Sounds/Pistol.wav", &w->sdl->wav_spect[0],
	&w->sdl->wav_buff[0], &w->sdl->wav_len[0]);

	SDL_LoadWAV("Sounds/step.wav", &w->sdl->wav_spect[1],
	&w->sdl->wav_buff[1], &w->sdl->wav_len[1]);
	
	SDL_LoadWAV("Sounds/main.wav", &w->sdl->wav_spect[2],
	&w->sdl->wav_buff[2], &w->sdl->wav_len[2]);
	
	w->sdl->audio_device[0] = SDL_OpenAudioDevice(NULL, 0,
	&w->sdl->wav_spect[0], NULL, 0);
	
	w->sdl->audio_device[1] = SDL_OpenAudioDevice(NULL, 0,
	&w->sdl->wav_spect[1], NULL, 0);
	
	w->sdl->audio_device[2] = SDL_OpenAudioDevice(NULL, 0,
	&w->sdl->wav_spect[2], NULL, 0);
}

void	ft_load_sound(t_wolf3d *w)
{
	w->t.sound_old_time = w->t.sound_time;
	w->t.sound_time = SDL_GetTicks();
	w->t.change_of_time = (w->t.sound_time - w->t.sound_old_time);
	w->t.sound_sum_time += w->t.change_of_time;
	if (w->t.sound_sum_time >= w->t.play_time && w->sdl->i == 1)
	{
		w->t.sound_sum_time = 0;
		SDL_QueueAudio(w->sdl->audio_device[1], w->sdl->wav_buff[1],
		w->sdl->wav_len[1]);
		SDL_PauseAudioDevice(w->sdl->audio_device[1], 0);
	}
}

void	ft_play_shot(t_wolf3d *w)
{
	if (w->t.flag == 1)
	{
		SDL_QueueAudio(w->sdl->audio_device[0], w->sdl->wav_buff[0],
		w->sdl->wav_len[0]);
		SDL_PauseAudioDevice(w->sdl->audio_device[0], 0);
		w->t.flag = 0;
	}
	w->anim.start_am = 1;
}

void	ft_play_music(t_wolf3d *w)
{
	if (w->arr[5] == 1)
	{
		SDL_QueueAudio(w->sdl->audio_device[2], w->sdl->wav_buff[2],
		w->sdl->wav_len[2]);
		SDL_PauseAudioDevice(w->sdl->audio_device[2], 0);
		w->arr[5] = 0;
	}	
}
