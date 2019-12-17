/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:10:50 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/17 21:28:24 by tjuana           ###   ########.fr       */
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

SDL_Surface		*ft_load_png(char *name, t_sdl *sdl)
{
	SDL_Surface* load = NULL;
	
	sdl->win_surface = SDL_GetWindowSurface(sdl->win);
	if(!(IMG_Init(IMG_INIT_PNG)& IMG_INIT_PNG))
		ft_sdl_init_error(sdl);
	SDL_Rect bg_flower;
    bg_flower.w = WIN_WIDTH;
    bg_flower.h = WIN_HEIGHT;
    bg_flower.x = 0;
    bg_flower.y = 0;
	sdl->win_surface = SDL_GetWindowSurface(sdl->win);
	if((load = IMG_Load(name)) == NULL)
		ft_sdl_init_error(sdl);
	else
		if((sdl->wall_surface = SDL_ConvertSurface(load, sdl->win_surface->format, 0)) == NULL)
			ft_sdl_init_error(sdl);
	SDL_BlitScaled(sdl->wall_surface, NULL, sdl->win_surface, &bg_flower);
	
	
		

	
	// int h = WIN_HEIGHT;
	// int w = WIN_WIDTH;

	// Convert SDL surface to a texture
	
	// if((sdl->test = SDL_CreateTextureFromSurface(sdl->renderer, sdl->wall_texture)) == NULL)
	// 	ft_sdl_init_error(sdl);

    // Grab dimensions
	// if (SDL_QueryTexture(sdl->test, NULL, NULL, &w, &h) != 0)
	// 	ft_sdl_init_error(sdl);
return (sdl->wall_surface);
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
		
	free(w->sdl->surfaces);
	free(w->sdl->pixels);
	
	if (w->map.s_count > 0)
	{
		free(w->map.s_ord);
		free(w->map.s_dst);
		free(w->map.sprite);
	}
	
	free(w->map.map);
	//free(w->sdl);
	
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

