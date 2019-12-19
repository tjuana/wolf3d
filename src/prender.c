//
// Created by Nymphadora Shelly on 04/12/2019.
//
#include "prender.h"
//#include "wolf3d.h"

void player_init(t_player *player, t_xy *v, float *angle, int *n)//init data for LoadData function
{
    //player = (struct player) { {v->x, v->y, 0}, {0,0,0}, *angle,0,0,0, n };
    player->where.x = v->x;
    player->where.y = v->y;
    player->where.z = 0;
    player->velocity.x = 0;
    player->velocity.y = 0;
    player->velocity.z = 0;
    player->angle = *angle;
    player->anglesin = 0;
    player->anglecos = 0;
    player->yaw = 0;
    player->sector = *n;
}

void LoadData(char *ag, t_player *player)//this function reads a new map format
{

    FILE* fp = fopen(ag, "rt");
    if(!fp) { perror(ag); exit(1); }
    char Buf[256];
    char word[256];
    char *ptr;
    float angle;
    t_xy *vert = NULL;//, v;
    t_xy v;
    int n;
    int m;
    static int p;//the first time is 0. Is a rule for all statics variables
    int NumVertices = 0;
    while(fgets(Buf, sizeof Buf, fp))
        switch(sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
        {
            case 'v': // vertex
                for(sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1; )
                { vert = realloc(vert, ++NumVertices * sizeof(*vert)); vert[NumVertices-1] = v; }
                break;
            case 's': // sector
                if(p == 0)
                {
                    player->sectors = malloc(NumSectors * sizeof(*player->sectors));//allocate memory if first time
                    p++;
                }
                player->sectors = realloc(player->sectors, ++NumSectors * sizeof(*player->sectors));//reallocate memory
                t_sector  *sect = &player->sectors[NumSectors-1];//SECT CREATED
                int* num = NULL;
                sscanf(ptr += n, "%f%f%n", &sect->floor,&sect->ceil, &n);
                for(m=0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; )
                { num = realloc(num, ++m * sizeof(*num)); num[m-1] = word[0]=='x' ? -1 : atoi(word); }
                sect->npoints   = m /= 2;
                sect->neighbors = malloc( (m  ) * sizeof(*sect->neighbors) );
                sect->vertex    = malloc( (m+1) * sizeof(*sect->vertex)    );
                for(n=0; n<m; ++n) sect->neighbors[n] = num[m + n];
                for(n=0; n<m; ++n) sect->vertex[n+1]  = vert[num[n]]; // TODO: Range checking
                sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
                free(num);
                break;
            case 'p':; // player

                sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle,&n);
                player_init(player, &v, &angle, &n); // TODO: Range checking
                player->where.z = player->sectors[player->sector].floor + EyeHeight;
        }
    fclose(fp);
    free(vert);
}

void UnloadData(t_player *player)
{
    for(unsigned a=0; a<NumSectors; ++a) free(player->sectors[a].vertex);
    for(unsigned a=0; a<NumSectors; ++a) free(player->sectors[a].neighbors);
    free(player->sectors);
    player->sectors    = NULL;
    NumSectors = 0;
}

static SDL_Surface* surface = NULL;
/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
static void vline(int x, int y1,int y2, int top,int middle,int bottom)
{
    int *pix = (int*) surface->pixels;
    y1 = clamp(y1, 0, H-1);
    y2 = clamp(y2, 0, H-1);
    if(y2 == y1)
        pix[y1*W+x] = middle;
    else if(y2 > y1)
    {
        pix[y1*W+x] = top;
        for(int y=y1+1; y<y2; ++y) pix[y*W+x] = middle;
        pix[y2*W+x] = bottom;
    }
}
/* MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
 * also updates their anglesin/anglecos/sector properties properly.
 */
void MovePlayer(float dx, float dy, t_player *player)
{
    float px = player->where.x;
    float py = player->where.y;
    /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, PointSide will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    const t_sector * const sect = &player->sectors[player->sector];
    const t_xy* const vert = sect->vertex;
    for(unsigned s = 0; s < sect->npoints; ++s)
        if(sect->neighbors[s] >= 0
           && IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
           && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
        {
            player->sector = sect->neighbors[s];
            break;
        }

    player->where.x += dx;
    player->where.y += dy;
    player->anglesin = sinf(player->angle);
    player->anglecos = cosf(player->angle);
}

void DrawScreen(t_player *player)
{
    /* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
    float vx1;
    float vy1;
    float vx2;
    float vy2;
    /* Rotate them around the player's view */
    float pcos;
    float psin;
    float tx1;
    float tz1;
    float tx2;
    float tz2;
    float nearz;
    float farz;
    float nearside;
    float farside;
    t_xy i1;
    t_xy i2;
    /* Do perspective transformation */
    float xscale1;
    float yscale1;
    float xscale2;
    float yscale2;
    int x1;
    int x2;
    /* Acquire the floor and ceiling heights, relative to where the player's view is */
    float yceil;
    float yfloor;
    /* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
    int neighbor;
    float nyceil;
    float nyfloor;
    /* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
    int y1a;
    int y1b;
    int y2a;
    int y2b;
    int ny1a;
    int ny1b;
    int ny2a;
    int ny2b;
    /* Render the wall. */
    int beginx;
    int endx;
    int x;
    /* Calculate the Z coordinate for this point. (Only used for lighting.) */
    int z;
    /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
    int ya;
    int cya;
    int yb;
    int cyb;
    /* Same for _their_ floor and ceiling */
    int nya;
    int cnya;
    int nyb;
    int cnyb;

    enum { MaxQueue = 32 };  // maximum number of pending portal renders
    struct item { int sectorno,sx1,sx2; } queue[MaxQueue], *head=queue, *tail=queue;
    int ytop[W]={0};
    int ybottom[W];
    int renderedsectors[NumSectors];
    for(unsigned x=0; x<W; ++x) ybottom[x] = H-1;
    for(unsigned n=0; n<NumSectors; ++n) renderedsectors[n] = 0;

    /* Begin whole-screen rendering from where the player is. */
    *head = (struct item) { player->sector, 0, W-1 };
    if(++head == queue+MaxQueue) head = queue;

    do {
        /* Pick a sector & slice from the queue to draw */
        const struct item now = *tail;
        if(++tail == queue+MaxQueue) tail = queue;

        if(renderedsectors[now.sectorno] & 0x21) continue; // Odd = still rendering, 0x20 = give up
        ++renderedsectors[now.sectorno];
        const t_sector* const sect = &player->sectors[now.sectorno];//SECT CREATED
        /* Render each wall of this sector that is facing towards player. */
        for(unsigned s = 0; s < sect->npoints; ++s)
        {
            /* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
            vx1 = sect->vertex[s+0].x - player->where.x;
            vy1 = sect->vertex[s+0].y - player->where.y;
            vx2 = sect->vertex[s+1].x - player->where.x;
            vy2 = sect->vertex[s+1].y - player->where.y;
            /* Rotate them around the player's view */
            pcos = player->anglecos;
            psin = player->anglesin;
            tx1 = vx1 * psin - vy1 * pcos;
            tz1 = vx1 * pcos + vy1 * psin;
            tx2 = vx2 * psin - vy2 * pcos;
            tz2 = vx2 * pcos + vy2 * psin;
            /* Is the wall at least partially in front of the player? */
            if(tz1 <= 0 && tz2 <= 0) continue;
            /* If it's partially behind the player, clip it against player's view frustrum */
            if(tz1 <= 0 || tz2 <= 0)
            {
                nearz = 1e-4f;
                farz = 5;
                nearside = 1e-5f;
                farside = 20.f;
                // Find an intersection between the wall and the approximate edges of player's view
                i1 = Intersect(tx1,tz1,tx2,tz2, -nearside,nearz, -farside,farz);
                i2 = Intersect(tx1,tz1,tx2,tz2,  nearside,nearz,  farside,farz);
                if(tz1 < nearz) { if(i1.y > 0) { tx1 = i1.x; tz1 = i1.y; } else { tx1 = i2.x; tz1 = i2.y; } }
                if(tz2 < nearz) { if(i1.y > 0) { tx2 = i1.x; tz2 = i1.y; } else { tx2 = i2.x; tz2 = i2.y; } }
            }
            /* Do perspective transformation */
            xscale1 = hfov / tz1;
            yscale1 = vfov / tz1;
            x1 = W/2 - (int)(tx1 * xscale1);
            xscale2 = hfov / tz2;
            yscale2 = vfov / tz2;
            x2 = W/2 - (int)(tx2 * xscale2);
            if(x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) continue; // Only render if it's visible
            /* Acquire the floor and ceiling heights, relative to where the player's view is */
            yceil  = sect->ceil  - player->where.z;
            yfloor = sect->floor - player->where.z;
            /* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
            neighbor = sect->neighbors[s];
            nyceil=0;
            nyfloor=0;
            if(neighbor >= 0) // Is another sector showing through this portal? This permit us draw other sectors after the one where we are
            {
                nyceil  = player->sectors[neighbor].ceil  - player->where.z;
                nyfloor = player->sectors[neighbor].floor - player->where.z;
            }
            /* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
            y1a  = H/2 - (int)(Yaw(yceil, tz1, player) * yscale1);
            y1b = H/2 - (int)(Yaw(yfloor, tz1, player) * yscale1);
            y2a  = H/2 - (int)(Yaw(yceil, tz2, player) * yscale2);
            y2b = H/2 - (int)(Yaw(yfloor, tz2, player) * yscale2);
            /* The same for the neighboring sector */
            ny1a = H/2 - (int)(Yaw(nyceil, tz1, player) * yscale1);
            ny1b = H/2 - (int)(Yaw(nyfloor, tz1, player) * yscale1);
            ny2a = H/2 - (int)(Yaw(nyceil, tz2, player) * yscale2);
            ny2b = H/2 - (int)(Yaw(nyfloor, tz2, player) * yscale2);
            /* Render the wall. */
            beginx = max(x1, now.sx1);
            endx = min(x2, now.sx2);
            for(x = beginx; x <= endx; ++x)
            {
                /* Calculate the Z coordinate for this point. (Only used for lighting.) */
                z = ((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
                /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
                ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a;
                cya = clamp(ya, ytop[x],ybottom[x]); // top
                yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b;
                cyb = clamp(yb, ytop[x],ybottom[x]); // bottom
                /* Render ceiling: everything above this sector's ceiling height. */
                vline(x, ytop[x], cya-1, 0x111111 ,0x222222,0x111111);
                /* Render floor: everything below this sector's floor height. */
                vline(x, cyb+1, ybottom[x], 0x0000FF,0x0000AA,0x0000FF);
                /* Is there another sector behind this edge? */
                if(neighbor >= 0)
                {
                    /* Same for _their_ floor and ceiling */
                    nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a;
                    cnya = clamp(nya, ytop[x],ybottom[x]);
                    nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b;
                    cnyb = clamp(nyb, ytop[x],ybottom[x]);
                    /* If our ceiling is higher than their ceiling, render upper wall */
                    unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
                    vline(x, cya, cnya-1, 0, x==x1||x==x2 ? 0 : r1, 0); // Between our and their ceiling
                    ytop[x] = clamp(max(cya, cnya), ytop[x], H-1);   // Shrink the remaining window below these ceilings
                    /* If our floor is lower than their floor, render bottom wall */
                    vline(x, cnyb+1, cyb, 0, x==x1||x==x2 ? 0 : r2, 0); // Between their and our floor
                    ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
                }
                else
                {
                    /* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
                    unsigned r = 0x010101 * (255-z);
                    vline(x, cya, cyb, 0, x==x1||x==x2 ? 0 : r, 0);
                }
            }
            /* Schedule the neighboring sector for rendering within the window formed by this wall. */
            if(neighbor >= 0 && endx >= beginx && (head+MaxQueue+1-tail)%MaxQueue)
            {
                *head = (struct item) { neighbor, beginx, endx };
                if(++head == queue+MaxQueue) head = queue;
            }
        } // for s in sector's edges
        ++renderedsectors[now.sectorno];
    } while(head != tail); // render any other queued sectors
}


int main(int ac, char **ag)
{
    t_subevents se;
    t_mouse ms;
    t_player player;
    t_others ot;
    t_sector_ops op;

    if (ac < 2 || ac > 2)
    {
        printf("map error");
        return (0);
    }
    se.quit = 0;
    LoadData(ag[1], &player);//load map and init typedef t_player data
    SDL_Window* window = NULL;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
            {
            surface = SDL_GetWindowSurface(window);
            SDL_UpdateWindowSurface( window );
            SDL_ShowCursor(SDL_DISABLE);//NOT SHOW MOUSE CURSOR
            se.wsad[0] = 0;
            se.wsad[1] = 0;
            se.wsad[2] = 0;
            se.wsad[3] = 0;
            se.falling = 1;
            se.ground = 0;
            ot.moving = 0;
            se.ducking = 0;
            ms.yaw = 0;
            while (!se.quit)
            {
                DrawScreen(&player);
                SDL_UpdateWindowSurface( window );
                /* Vertical collision detection */
                op.eyeheight = se.ducking ? DuckHeight : EyeHeight;
                se.ground = !se.falling;
                jumps(&se, &player, &op, &ot);
                sectors_ops(&op, &player, &ot, &se);
                if (!events(&se, &player))
                    return(0);
                mouse_movement(&ms, &player);/* mouse aiming */
                vectors_vel_dir(&player, &se, &ot);
                MovePlayer(0, 0, &player);//Refresh Vectors. start movement in 0//if this line is in vectors_vel_dir slomaet programmy whe is running, is needed here
            }
            UnloadData(&player);
            SDL_Quit();
        }
    }
    return 0;
}