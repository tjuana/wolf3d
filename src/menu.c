/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:54:16 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/26 19:38:35 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static void ft_menu_button(t_wolf3d *w)
**	Function for buttons
** **************************************************************************
*/

static void	ft_menu_button(t_wolf3d *w, int x, int y, int button_id)
{
	button_id += 0;
	if (((x > 1) && (x < 2)) && ((y > 1) && (y < 2)))
	{
		printf("button test\n");
	}
	w->temp += 0;
}

/*
** **************************************************************************
**	static void ft_show_authors(t_wolf3d *w)
**	Function will show authors when pressed "How to play"
** **************************************************************************
*/

static void	ft_menu_authors(t_wolf3d *w)
{
	w->temp += 0;
}

/*
** **************************************************************************
**	static void ft_show_authors(t_wolf3d *w)
**	Function will show guide when pressed "How to play"
** **************************************************************************
*/

static void	ft_menu_guide(t_wolf3d *w)
{
	w->temp += 0;
}


/*
** **************************************************************************
**	void ft_menu(t_wolf3d *w)
**	Function will show user our menu
** **************************************************************************
*/

void	ft_menu(t_wolf3d *w)
{
	int	menu_x;
	int	menu_y;
	int	tmp;

	tmp = 0;
	w->sdl->font.sz = 72;
	menu_x = (WIN_WIDTH / 2) - (5.5 * 25);
	menu_y = WIN_HEIGHT / 2;
	w->sdl->font.color.a = 0;
	w->sdl->font.color.b = 63;
	w->sdl->font.color.g = 23;
	w->sdl->font.color.r = 73;
	ft_putstr_sdl(w, "Play", menu_x, menu_y - (w->sdl->font.sz * 2));
	ft_putstr_sdl(w, "How to play", menu_x, menu_y - w->sdl->font.sz);
	ft_putstr_sdl(w, "Map editor", menu_x, menu_y);
	ft_putstr_sdl(w, "Authors", menu_x, menu_y + w->sdl->font.sz);
	ft_putstr_sdl(w, "Exit", menu_x, menu_y + (w->sdl->font.sz * 2));
	ft_menu_authors(w);
	ft_menu_guide(w);
	ft_menu_button(w, 0, 0, 0);
}
