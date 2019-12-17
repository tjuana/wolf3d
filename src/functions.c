
#include "prender.h"
/*
 * min: Choose smaller of two scalars.
 */
double min(double a, double b)
{
    return  (((a) < (b)) ? (a) : (b));
}
/*
 * max: Choose greater of two scalars.
 */
double max(double a, double b)
{
    return  (((a) > (b)) ? (a) : (b));
}
/*
 * clamp: fijar los valores d eun rango establecido
 */
float clamp(double a, double mi, double ma)
{
    return  (min(max(a,mi),ma));
}
/*
 * vxs: Vector cross product
 */
double vxs(double x0, double y0, double x1, double y1)
{
    return ((x0)*(y1) - (x1)*(y0));
}
/*
 * Overlap:  Determine whether the two number ranges overlap.
 */
int Overlap(double a0, double a1, double b0, double b1)
{
    return (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1));
}
/*
 * IntersectBox: Determine whether two 2D-boxes intersect.
 */
int IntersectBox(double x0, double y0, double x1, double y1,double x2, double y2, double x3, double y3)
{
   return (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3));
}
/*
 * PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
 */
double PointSide(double px, double py, double x0, double y0,double x1, double y1)
{
   return (vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0)));
}
/*
 * Intersect: Calculate the point of intersection between two lines.
 */
t_xy Intersect(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4)
{
    t_xy xy;
    xy.x = vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4));
    xy.y = vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4));
    return (xy);
}

//double Yaw(double y, double z)//problems with function
//{
//    return (y + z * player.yaw);
//}


