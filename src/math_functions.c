//
// Created by Nymphadora Shelly on 19/12/2019.
//

#include "wolf3d.h"
/*
 * min: Choose smaller of two scalars.
 */
float min(float a, float b)
{
    return  (((a) < (b)) ? (a) : (b));
}
/*
 * max: Choose greater of two scalars.
 */
float max(float a, float b)
{
    return  (((a) > (b)) ? (a) : (b));
}
/*
 * clamp: fijar los valores  eun rango establecido
 */
float clamp(float a, float mi, float ma)
{
    return  (min(max(a,mi),ma));
}
/*
 * vxs: Vector cross product
 */
float vxs(float x0, float y0, float x1, float y1)
{
    return ((x0)*(y1) - (x1)*(y0));
}
/*
 * Overlap:  Determine whether the two number ranges overlap.
 */
int Overlap(float a0, float a1, float b0, float b1)
{
    return (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1));
}
/*
 * IntersectBox: Determine whether two 2D-boxes intersect.
 */
int IntersectBox(float x0, float y0, float x1, float y1,float x2, float y2, float x3, float y3)
{
    return (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3));
}
/*
 * PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
 */
float PointSide(float px, float py, float x0, float y0,float x1, float y1)
{
    return (vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0)));
}
/*
 * Intersect: Calculate the point of intersection between two lines.
 */
t_xy Intersect(float x1, float y1, float x2, float y2,float x3, float y3, float x4, float y4)
{
    t_xy xy;
    xy.x = vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4));
    xy.y = vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4));
    return (xy);
}

float Yaw(float y, float z, t_player *player)
{
    return(y + z*player->yaw);
}
