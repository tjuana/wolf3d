/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_stats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:40:14 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/10 20:48:11 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static char	*ft_select_str(t_wolf3d *w)
**	Function to write data into printed string
** **************************************************************************
*/

static char		*ft_select_str(t_wolf3d *w)
{
	char	*res;

	res = NULL;
	w->pl.st.jetpack == 1 ? res = "Jetpack is on!" : 0;
	w->pl.st.jetpack == 0 ? res = "Jetpack is off!" : 0;
	res = "Door is locked";
	//resume, new game, quit, you died... (delay end return to menu)
	return(res);
}

/*
** **************************************************************************
**	void ft_pl_stats(t_wolf3d *w)
**	Function to print words
** **************************************************************************
*/

void			ft_pl_stats(t_wolf3d *w)
{
	char				*str;

	w->pl.st.jetpack = 3;
	str = ft_select_str(w);
	w->pl.st.font_sz = 70;
	ft_putstr_sdl(w, "Hey ho hip ho", WIN_WIDTH/2, WIN_HEIGHT/2);
}
