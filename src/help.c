/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:10:50 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/17 19:15:07 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// void			ft_bank_of_text(char *dir, t_wolf3d *w)
// {
	
	// struct dirent *de;  // Pointer for directory entry 
    // opendir() returns a pointer of DIR type.  
	// char	*name = NULL;
	
	// DIR *dr = opendir(dir); 
  
    // if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    // { 
    //     printf("Could not open current directory" ); 
    //     exit(-1);
    // } 
    // // for readdir()
	// char *c = ".png";
	// w->sdl->i = 0;
    // while ((de = readdir(dr)) != NULL)
	// {
		// if (ft_strstr(de->d_name, c))
		// {
			// printf("%s\n", de->d_name);
			// name = ft_strjoin(dir, de->d_name);

			// printf("%s\n",name);
			
			// w->sdl->test = ft_load_png("./Textures/MFLR8_1.png", w->sdl);
			// w->sdl->surfaces[i] = ft_sdl_load_bmp(de->d_name);
		// 	w->sdl->i++;
		// }
		// 
		// printf("%s\n", de->d_name);
		// w->sdl->surfaces[i]->refcount++;
		// printf("%d\n", w->sdl->surfaces[i]->refcount);
		// printf("%s\n", w->sdl->surfaces[0]->userdata);
		
	// }       
	
  
    // closedir(dr);
// }

SDL_Texture		*ft_load_png(char *name, t_sdl *sdl)
{
	SDL_Surface *tmp;
	SDL_Texture *text;
	
	if(!(IMG_Init(IMG_INIT_PNG)& IMG_INIT_PNG))
		ft_sdl_init_error(sdl);
	tmp = ft_my_malloc(sizeof(tmp));
	
	tmp = IMG_Load(name);
	int h = WIN_HEIGHT;
	int w = WIN_WIDTH;

	// Convert SDL surface to a texture
	if((text = SDL_CreateTextureFromSurface(sdl->renderer, tmp)) == NULL) {
		SDL_Log("Unable to create SDL Texture : %s : %s", name, IMG_GetError());
		exit(-1);
	}

    // Grab dimensions
	SDL_QueryTexture(text, NULL, NULL, &w, &h); 

	SDL_FreeSurface(tmp);
	
	sdl->test = text;
	
	return (0);
}

SDL_Surface		*ft_sdl_load_bmp(char *str)
{
	SDL_Surface	*temp;

	temp = SDL_LoadBMP(str);
	if (temp == NULL)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}

	return (temp);
}
		// if(tmp)
	// 	opt = SDL_ConvertSurface(tmp, sdl->surface->format, 0);
    // Convert SDL surface to a texture
	// SDL_GetColorKey(TempSurface, key);
	//Log("Texture Dimensions: %s : %d %d", Filename.c_str(), Width, Height);
	// TempSurface = TempSurface->format->next;
		// Uint32 *key = NULL;
	// if(TempSurface == NULL) {
	// 	Log("Unable to load image : %s : %s", name, IMG_GetError());
	// 	exit(-2);
	// }
int				ft_error(char *code)
{
	ft_putendl(code);
	exit(EXIT_FAILURE);
	return (1);
}

void			*ft_my_malloc(size_t s)
{
	void	*p;

	if (!(p = malloc(s)))
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
	SDL_CloseAudioDevice(w->sdl->audio_device[2]);
	SDL_FreeWAV(w->sdl->wav_buff[2]);
	free(w->sdl->wav_buff);
	free(w->sdl->wav_spect);
	free(w->sdl->wav_len);
	free(w->sdl->audio_device);
	
	// SDL_FreeSurface(*w->sdl->surfaces);
	SDL_FreeSurface(w->weapon_texture);
	SDL_FreeSurface(w->map_texture);
	SDL_FreeSurface(w->sdl->surface);
	free(w->sdl->surfaces);
	free(w->sdl->pixels);
	if (w->map.s_count > 0)
	{
		free(w->map.s_ord);
		free(w->map.s_dst);
		free(w->map.sprite);
	}
	
	free(w->map.map);
	// free(w->sdl);
	
	SDL_DestroyTexture(w->sdl->text);
	w->sdl->text = NULL;
	// SDL_DestroyTexture(w->sdl->test);
	// w->sdl->test = NULL;
	SDL_DestroyRenderer(w->sdl->renderer);
	SDL_DestroyWindow(w->sdl->win);
	
	SDL_Delay(777);
	
	IMG_Quit();
	SDL_Quit();
}

