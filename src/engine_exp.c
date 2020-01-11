/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:27:28 by drafe             #+#    #+#             */
/*   Updated: 2020/01/11 19:22:48 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	int engine_cross(t_player *pl, t_xy *v_start, t_xy *v_end)
**	Function to set t1 & t2
** **************************************************************************
*/

int		engine_cross(t_player *pl, t_xy *v_start, t_xy *v_end)
{
	t_xy i1;
	t_xy i2;

	/* Rotate them around the player's view */
	pl->t1.x = v_start->x * pl->anglesin - v_start->y * pl->anglecos;
	pl->t1.y = v_start->x * pl->anglecos + v_start->y * pl->anglesin;
	pl->t2.x = v_end->x * pl->anglesin - v_end->y * pl->anglecos;
	pl->t2.y = v_end->x * pl->anglecos + v_end->y * pl->anglesin;

	
	/* Is the wall at least partially in front of the player? */

	if((pl->t1.y <= 0) && (pl->t2.y <= 0))
		return (0);//continue

	/* If it's partially behind the player, clip it against player's view frustrum */
	//printf("ZZZZ v_end.x==%f v_end.y==%f v_start.x==%f v_start.y==%f \n", v_end->x, v_end->y, v_start->x, v_start->y);

	if((pl->t1.y <= 0) || (pl->t2.y <= 0))
	{
		// Find an intersection between the wall and the approximate edges of player's view
		i1 = Intersect(pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y, -pl->nearside, pl->nearz, -pl->farside, pl->farz);
		i2 = Intersect(pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y, pl->nearside, pl->nearz, pl->farside, pl->farz);
		if(pl->t1.y < pl->nearz) { if(i1.y > 0) { pl->t1.x = i1.x; pl->t1.y = i1.y; } else { pl->t1.x = i2.x; pl->t1.y = i2.y; } }
		if(pl->t2.y < pl->nearz) { if(i1.y > 0) { pl->t2.x = i1.x; pl->t2.y = i1.y; } else { pl->t2.x = i2.x; pl->t2.y = i2.y; } }

	}
	//printf("ZZZZ t1.x==%f t1.y==%f t2.x==%f t2.y==%f \n", pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y);
	return (1);
}
/*

			// Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector 
			v_start.x = sect->vertex[s + 0].x - pl->where.x;
			v_start.y = sect->vertex[s + 0].y - pl->where.y;
			v_end.x = sect->vertex[s + 1].x - pl->where.x;
			v_end.y = sect->vertex[s + 1].y - pl->where.y;
			// Rotate them around the player's view 
			pl->t1.x = v_start.x * pl->anglesin - v_start.y * pl->anglecos;
			pl->t1.y = v_start.x * pl->anglecos + v_start.y * pl->anglesin;
			pl->t2.x = v_end.x * pl->anglesin - v_end.y * pl->anglecos;
			pl->t2.y = v_end.x * pl->anglecos + v_end.y * pl->anglesin;
			//Is the wall at least partially in front of the player? 
			if(pl->t1.y <= 0 && pl->t2.y <= 0) continue;
			// If it's partially behind the player, clip it against player's view frustrum 
			if(pl->t1.y <= 0 || pl->t2.y <= 0)
			{
				// Find an intersection between the wall and the approximate edges of player's view
				i1 = Intersect(pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y, -pl->nearside, pl->nearz, -pl->farside, pl->farz);
				i2 = Intersect(pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y, pl->nearside, pl->nearz, pl->farside, pl->farz);
				if(pl->t1.y < pl->nearz) { if(i1.y > 0) { pl->t1.x = i1.x; pl->t1.y = i1.y; } else { pl->t1.x = i2.x; pl->t1.y = i2.y; } }
				if(pl->t2.y < pl->nearz) { if(i1.y > 0) { pl->t2.x = i1.x; pl->t2.y = i1.y; } else { pl->t2.x = i2.x; pl->t2.y = i2.y; } }
			}

*/

/*

			// Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector 
			v_start.x = sect->vertex[s + 0].x - pl->where.x;
			v_start.y = sect->vertex[s + 0].y - pl->where.y;
			v_end.x = sect->vertex[s + 1].x - pl->where.x;
			v_end.y = sect->vertex[s + 1].y - pl->where.y;
			// Rotate them around the player's view
			tx1 = v_start.x * pl->anglesin - v_start.y * pl->anglecos;
			tz1 = v_start.x * pl->anglecos + v_start.y * pl->anglesin;
			tx2 = v_end.x * pl->anglesin - v_end.y * pl->anglecos;
			tz2 = v_end.x * pl->anglecos + v_end.y * pl->anglesin;
			// Is the wall at least partially in front of the player?
			if(tz1 <= 0 && tz2 <= 0) continue;
			// If it's partially behind the player, clip it against player's view frustrum
			if(tz1 <= 0 || tz2 <= 0)
			{
				// Find an intersection between the wall and the approximate edges of player's view
				i1 = Intersect(tx1, tz1, tx2, tz2, -pl->nearside, pl->nearz, -pl->farside, pl->farz);
				i2 = Intersect(tx1, tz1, tx2, tz2, pl->nearside, pl->nearz, pl->farside, pl->farz);
				if(tz1 < pl->nearz) { if(i1.y > 0) { tx1 = i1.x; tz1 = i1.y; } else { tx1 = i2.x; tz1 = i2.y; } }
				if(tz2 < pl->nearz) { if(i1.y > 0) { tx2 = i1.x; tz2 = i1.y; } else { tx2 = i2.x; tz2 = i2.y; } }
			}

*/
		/*
		if(pl->t1.y < pl->nearz)
		{
			if(i1.y > 0)
			{
				pl->t1.x = i1.x;
				pl->t1.y = i1.y;
			}
			else
			{
				pl->t1.x = i2.x;
				pl->t1.y = i2.y;
			}
		}
		if(pl->t2.y < pl->nearz)
		{
			if(i1.y > 0)
			{
				pl->t2.x = i1.x;
				pl->t2.y = i1.y;
			}
			else
			{
				pl->t2.x = i2.x;
				pl->t2.y = i2.y;
			}
		}*/
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