/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:21:47 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/04 18:47:09 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H
# define WIN_HEIGHT 900
# define WIN_WIDTH 1600
# define TEXTURES_NUMBER 23
# define THREADS 10
# define TEX_W 64
# define TEX_H 64
# define ONE_ANIM 20
# define FULL_ANIM ONE_ANIM * 4 - 4
# define KEYS_NBR 66
# define MAX_DOORS_NBR 20

# define C_R 0x00FF0000
# define C_G 0x0000FF00
# define C_B 0x000000FF

typedef struct			s_const
{
	double				crs;
	double				srs;
	double				mcrs;
	double				msrs;
	double				camera_x_cnst;
	int					half_height;
}						t_const;

#endif
