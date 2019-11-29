/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_stats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:40:14 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/29 16:48:33 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_pl_stats(t_wolf3d *w)
{	
	SDL_version compile_version;
	const SDL_version *link_version;

	link_version = TTF_Linked_Version();
	SDL_TTF_VERSION(&compile_version);
	printf("compiled with SDL_ttf version: %d.%d.%d\n", 
        compile_version.major,
        compile_version.minor,
        compile_version.patch);
	printf("running with SDL_ttf version: %d.%d.%d\n", 
        link_version->major,
        link_version->minor,
        link_version->patch);
	w += 0;
}