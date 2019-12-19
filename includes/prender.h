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
#define W 800
#define H 600
/* Define various vision related constants */
#define EyeHeight  6    // Camera height from floor when standing
#define DuckHeight 2.5  // And when crouching
#define HeadMargin 1    // How much room there is above camera before the head hits the ceiling
#define KneeHeight 2    // How tall obstacles the player can simply walk over without jumping
#define hfov (0.73f*H)  // Affects the horizontal field of vision
#define vfov (.2f*H)    // Affects the vertical field of vision
//#define Yaw(y,z) (y + z*player.yaw)



/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */
/*static struct sector//have to be static
{
    float floor, ceil;
    struct xy { float x,y; } *vertex; // Each vertex has an x and y coordinate
    signed char *neighbors;           // Each edge may have a corresponding neighboring sector
    unsigned npoints;                 // How many vertexes there are
} *sectors = NULL;*/

typedef struct s_xy
{
    float x;
    float y;
} t_xy;

typedef struct s_sector//have to be static
{
    float floor, ceil;
    t_xy *vertex; // Each vertex has an x and y coordinate
    signed char *neighbors;           // Each edge may have a corresponding neighboring sector
    unsigned npoints;                 // How many vertexes there are
}   t_sector;//*sectors = NULL;

static unsigned NumSectors = 0;// have to be static

/* Player: location */

typedef struct s_xyz
{
    float x;
    float y;
    float z;
} t_xyz;



typedef struct s_player
{
    t_xyz where;      // Current position
    t_xyz velocity;   // Current motion vector
    float angle;
    float anglesin;
    float anglecos;
    float yaw;   // Looking towards (and sin() and cos() thereof)
    unsigned sector;// Which sector the player is currently in
    t_sector *sectors;
} t_player;


typedef struct s_subevents
{
    SDL_Event ev;
    int *wsad[4];
    int ground;
    int falling;
    int ducking;
    int quit;
}   t_subevents;

typedef struct s_mouse
{
    int x;
    int y;
    float yaw;

}   t_mouse;
typedef struct s_coords
{
    double x0;
    double y0;
    double x1;
    double y1;
    double x2;
    double y2;
    double x3;
    double y3;
    double x4;
    double y4;
} t_coords;

typedef struct s_others
{
    float move_vec[2];
    int moving;
} t_others;
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
void MovePlayer(float dx, float dy, t_player *player);
void DrawScreen();
double Yaw(double y, double z, t_player *player);
//static void vlines(int x, int y1,int y2, int top,int middle,int bottom, SDL_Surface *surf);


#endif //DOOM_W_PRENDER_H


