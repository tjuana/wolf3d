/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:10:50 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/03 16:36:33 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_bank_of_text(char *dir, t_wolf3d *w)
{
	
	struct dirent *de;  // Pointer for directory entry 
    // opendir() returns a pointer of DIR type.  
	char	*name;
	DIR *dr = opendir(dir); 
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        printf("Could not open current directory" ); 
        exit(-1);
    } 
	
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
    // for readdir()
	char *c = ".png";
	w->sdl->i = 0;
    while ((de = readdir(dr)) != NULL)
	{
		if (ft_strstr(de->d_name, c))
		{
			// printf("%s\n", de->d_name);
			name = ft_strjoin(dir, de->d_name);
			printf("%s\n",name);
			w->sdl->test = ft_load_png(name, w->sdl);
			// w->sdl->surfaces[i] = ft_sdl_load_bmp(de->d_name);
			w->sdl->i++;
		}
		// 
		// printf("%s\n", de->d_name);
		// w->sdl->surfaces[i]->refcount++;
		// printf("%d\n", w->sdl->surfaces[i]->refcount);
		// printf("%s\n", w->sdl->surfaces[0]->userdata);

    }       // 
	
  
    closedir(dr);
}

SDL_Texture		*ft_load_png(char *name, t_sdl *sdl)
{
	SDL_Surface* TempSurface;
	
	TempSurface = IMG_Load(name);
	
	int w = WIN_HEIGHT;
	int h = WIN_WIDTH;

	// if(TempSurface == NULL) {
	// 	Log("Unable to load image : %s : %s", name, IMG_GetError());
	// 	exit(-2);
	// }
	if(TempSurface == NULL)
		ft_sdl_init_error(sdl);
    // Convert SDL surface to a texture
	if((sdl->test = SDL_CreateTextureFromSurface(sdl->renderer, TempSurface)) == NULL)
		ft_sdl_init_error(sdl);
    // Grab dimensions
	SDL_QueryTexture(sdl->test, NULL, NULL, &w, &h);

	//Log("Texture Dimensions: %s : %d %d", Filename.c_str(), Width, Height);
	// TempSurface = TempSurface->format->next;
	return (sdl->test);
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
	// free(w->sdl);
	w->sdl->text ? SDL_DestroyTexture(w->sdl->text) : 0;
	//w->sdl->test ? SDL_DestroyTexture(w->sdl->test) : 0;//SEGFAULT

	SDL_DestroyRenderer(w->sdl->renderer);
	SDL_DestroyWindow(w->sdl->win);	
	IMG_Quit();
	SDL_Quit();
}

