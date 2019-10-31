/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:10:50 by tjuana            #+#    #+#             */
/*   Updated: 2019/10/31 15:51:00 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface		*ft_sdl_load_bmp(char *str)
{
	SDL_Surface	*texture;

	texture = SDL_LoadBMP(str);
	if (texture == NULL)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
	return (texture);
}
int				ft_error(char *code)
{
	ft_putendl(code);
	exit(EXIT_FAILURE);
	return (1);
}

void			*ft_my_malloc(size_t s)
{
	void	*p;
	
	if(!(p = malloc(s)))
	{
		perror("Malloc failed!");
		exit(EXIT_FAILURE);
	}
	return (p);
}

int				ft_cleanmem(t_list **lst)
{
	t_list	*next;
	
	while (*lst)
	{
		next = (*lst)->next;
		ft_memdel(&(*lst)->content);
		ft_memdel((void**)lst);
		*lst = next;
	}
	return (0);
}

void			ft_clean_sdl(t_wolf3d *w)
{
	SDL_CloseAudioDevice(w->sdl->audio_device[0]);
	SDL_FreeWAV(w->sdl->wav_buff[0]);
	SDL_CloseAudioDevice(w->sdl->audio_device[1]);
	SDL_FreeWAV(w->sdl->wav_buff[1]);
	free(w->sdl->wav_buff);
	free(w->sdl->wav_spect);
	free(w->sdl->wav_len);
	free(w->sdl->audio_device);
	free(w->sdl->textures);
	free(w->sdl->pixels);
	
	if (w->map.s_count > 0)
	{
		free(w->map.s_ord);
		free(w->map.s_dst);
		//free(w->map.sprite);
	}
	free(w->map.map);
	SDL_DestroyTexture(w->sdl->text);
	SDL_DestroyRenderer(w->sdl->renderer);
	SDL_DestroyWindow(w->sdl->win);
	SDL_Delay(2000);
	SDL_Quit();
}