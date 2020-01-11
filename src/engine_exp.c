/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:27:28 by drafe             #+#    #+#             */
/*   Updated: 2020/01/11 21:16:47 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	int engine_cross(t_player *pl, t_sector *sect, unsigned s)
**	Function to find intersections and set t1 & t2
**	t1.y - tz1
** **************************************************************************
*/

int		engine_cross(t_player *pl, int sec_n, unsigned s)
{
	t_xy	i1;
	t_xy	i2;
	t_xy	v_start;
	t_xy	v_end;

	//Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector
	v_start.x = pl->sectors[sec_n].vertex[s + 0].x - pl->where.x;
	v_start.y = pl->sectors[sec_n].vertex[s + 0].y - pl->where.y;
	v_end.x = pl->sectors[sec_n].vertex[s + 1].x - pl->where.x;
	v_end.y = pl->sectors[sec_n].vertex[s + 1].y - pl->where.y;
	//Rotate them around the player's view
	pl->t1.x = v_start.x * pl->anglesin - v_start.y * pl->anglecos;
	pl->t1.y = v_start.x * pl->anglecos + v_start.y * pl->anglesin;
	pl->t2.x = v_end.x * pl->anglesin - v_end.y * pl->anglecos;
	pl->t2.y = v_end.x * pl->anglecos + v_end.y * pl->anglesin;
	//Is the wall at least partially in front of the player?
	if((pl->t1.y <= 0) && (pl->t2.y <= 0))
		return (0);//continue
	//If it's partially behind the player, cut it against player's view
	if((pl->t1.y <= 0) || (pl->t2.y <= 0))
	{
		// Find an intersection between the wall and the approximate edges of player's view
		i1 = Intersect(pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y, -pl->nearside, pl->nearz, -pl->farside, pl->farz);
		i2 = Intersect(pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y, pl->nearside, pl->nearz, pl->farside, pl->farz);
		if(pl->t1.y < pl->nearz && i1.y > 0)
			pl->t1 = i1;
		if(pl->t1.y < pl->nearz && i1.y < 0)
			pl->t1 = i2;
		if(pl->t2.y < pl->nearz && i1.y > 0)
			pl->t2 = i1;
		if(pl->t2.y < pl->nearz && i1.y < 0)
			pl->t2 = i2;
	}
	

	return (1);
}
/*
	printf("CROSS_1 i1.x==%f i1.y==%f i2.x==%f i2.y==%f \n", i1.x, i1.y, i2.x, i2.y);
	printf("CROSS_2 t1.x==%f t1.y==%f t2.x==%f t2.y==%f \n", pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y);
	//CROSS_1 i1.x==1.203689 i1.y==-0.300819 i2.x==2.036359 i2.y==0.509177
	//CROSS_2 t1.x==2.036359 t1.y==0.509177 t2.x==4.838886 t2.y==3.235392

	//CROSS_1 i1.x==2.111018 i1.y==0.000000 i2.x==0.000000 i2.y==0.000000
	//CROSS_2 t1.x==4.838886 t1.y==3.235392 t2.x==2.049765 t2.y==6.102586

if(pl->t1.y < pl->nearz)
{
	pl->t1 = i2;
	(i1.y > 0) ? pl->t1 = i1 : pl->t1;
	//(i1.y > 0) ? pl->t1 = i1 : i2;
}
if(pl->t2.y < pl->nearz)
{
	pl->t2 = i2;
	(i1.y > 0) ? pl->t2 = i1 : pl->t2;
	//(i1.y > 0) ? pl->t2 = i1 : i2;
}
*/
/*
printf(" t1.x==%f t1.y==%f t2.x==%f t2.y==%f \n", tx1, tz1, tx2, tz2);
			printf(" t1.x==%f t1.y==%f t2.x==%f t2.y==%f \n", pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y);
		//printf("CROSS_1 v_end.x==%f v_end.y==%f v_start.x==%f v_start.y==%f \n", v_end->x, v_end->y, v_start->x, v_start->y);
	//printf("CROSS_2 t1.x==%f t1.y==%f t2.x==%f t2.y==%f \n", pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y);		
*/
/*
if(pl->t1.y < pl->nearz)
{
	if(i1.y > 0)
		pl->t1 = i1;
	else
		pl->t1 = i2;
}
if(pl->t2.y < pl->nearz)
{
	if(i1.y > 0)
		pl->t2 = i1;
	else
		pl->t2 = i2;
}
*/
/*
** **************************************************************************
**	void engine_scale(t_player *pl, float tz1, float tz2)
**	Function to scale floor & ceil
** **************************************************************************
*/

void	engine_scale(t_player *pl, float tz1, float tz2)
{
	pl->scale_1.x = hfov / tz1;
	pl->scale_1.y = vfov / tz1;
	pl->scale_2.x = hfov / tz2;
	pl->scale_2.y = vfov / tz2;
	//Do perspective transformation
	pl->x1 = WIN_W / 2 - (int)(pl->t1.x * pl->scale_1.x);
	pl->x2 = WIN_W / 2 - (int)(pl->t2.y * pl->scale_2.x);
	//Project our ceiling & floor heights into screen coordinates (Y coordinate)
	pl->ceil.y1a = WIN_H / 2 - (int)(Yaw(pl->ceil.yceil, tz1, pl) * pl->scale_1.y);
	pl->floor.y1b = WIN_H / 2 - (int)(Yaw(pl->floor.yfloor, tz1, pl) * pl->scale_1.y);
	pl->ceil.y2a = WIN_H / 2 - (int)(Yaw(pl->ceil.yceil, tz2, pl) * pl->scale_2.y);
	pl->floor.y2b = WIN_H / 2 - (int)(Yaw(pl->floor.yfloor, tz2, pl) * pl->scale_2.y);
	//The same for the neighboring sector
	pl->ceil.ny1a = WIN_H / 2 - (int)(Yaw(pl->ceil.nyceil, tz1, pl) * pl->scale_1.y);
	pl->floor.ny1b = WIN_H / 2 - (int)(Yaw(pl->floor.nyfloor, tz1, pl) * pl->scale_1.y);
	pl->ceil.ny2a = WIN_H / 2 - (int)(Yaw(pl->ceil.nyceil, tz2, pl) * pl->scale_2.y);
	pl->floor.ny2b = WIN_H / 2 - (int)(Yaw(pl->floor.nyfloor, tz2, pl) * pl->scale_2.y);
}