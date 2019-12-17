//
// Created by Nymphadora Shelly on 04/12/2019.
//

#ifndef DOOM_W_PRENDER_H
#define DOOM_W_PRENDER_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

/* Define window size */
#define W 608
#define H 480
/* Define various vision related constants */
#define EyeHeight  6    // Camera height from floor when standing
#define DuckHeight 2.5  // And when crouching
#define HeadMargin 1    // How much room there is above camera before the head hits the ceiling
#define KneeHeight 2    // How tall obstacles the player can simply walk over without jumping
#define hfov (0.73f*H)  // Affects the horizontal field of vision
#define vfov (.2f*H)    // Affects the vertical field of vision
#define Yaw(y,z) (y + z*player.yaw)

/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */
static struct sector
{
    float floor, ceil;
    struct xy { float x,y; } *vertex; // Each vertex has an x and y coordinate
    signed char *neighbors;           // Each edge may have a corresponding neighboring sector
    unsigned npoints;                 // How many vertexes there are
} *sectors = NULL;
static unsigned NumSectors = 0;

/* Player: location */
static struct player
{
    struct xyz { float x,y,z; } where,      // Current position
            velocity;   // Current motion vector
    float angle, anglesin, anglecos, yaw;   // Looking towards (and sin() and cos() thereof)
    unsigned sector;                        // Which sector the player is currently in
} player;

typedef struct s_xy
{
    float x;
    float y;
} t_xy;

double min(double a, double b);
double max(double a, double b);
float clamp(double a, double mi, double ma);
double vxs(double x0, double y0, double x1, double y1);
int Overlap(double a0, double a1, double b0, double b1);
int IntersectBox(double x0, double y0, double x1, double y1,double x2, double y2, double x3, double y3);
double PointSide(double px, double py, double x0, double y0,double x1, double y1);
t_xy Intersect(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4);
//double Yaw(double y, double z);
void LoadData();
void UnloadData();
void MovePlayer(float dx, float dy);
void DrawScreen();
//static void vlines(int x, int y1,int y2, int top,int middle,int bottom, SDL_Surface *surf);


#endif //DOOM_W_PRENDER_H


