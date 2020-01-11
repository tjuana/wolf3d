//
// Created by Nymphadora Shelly on 04/12/2019.
//
#include "wolf3d.h"

void player_init(t_player *pl, t_xy *v, float *angle, int *n)//init data for LoadData function
{
    //player = (struct player) { {v->x, v->y, 0}, {0,0,0}, *angle,0,0,0, n };
    pl->where.x = v->x;
    pl->where.y = v->y;
    pl->where.z = 0;
    pl->velocity.x = 0;
    pl->velocity.y = 0;
    pl->velocity.z = 0;
    pl->angle = *angle;
    pl->anglesin = 0;
    pl->anglecos = 0;
    pl->yaw = 0;
    pl->sector = *n;
	pl->ceil.nyceil = 0;
	pl->floor.nyfloor = 0;
	/* If it's partially behind the player, clip it against player's view frustrum */
	pl->nearz = 1e-4f;
	pl->farz = 5;
	pl->nearside = 1e-5f;
	pl->farside = 20.f;
}

void LoadData(char *ag, t_player *pl)//this function reads a new map format
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
                    pl->sectors = malloc(NumSectors * sizeof(*pl->sectors));//allocate memory if first time
                    p++;
                }
                pl->sectors = realloc(pl->sectors, ++NumSectors * sizeof(*pl->sectors));//reallocate memory
                t_sector  *sect = &pl->sectors[NumSectors-1];//SECT CREATED
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
                player_init(pl, &v, &angle, &n); // TODO: Range checking
                pl->where.z = pl->sectors[pl->sector].floor + EyeHeight;
        }
    fclose(fp);
    free(vert);
}

void UnloadData(t_player *pl)
{
    for(unsigned a=0; a<NumSectors; ++a) free(pl->sectors[a].vertex);
    for(unsigned a=0; a<NumSectors; ++a) free(pl->sectors[a].neighbors);
    free(pl->sectors);
    pl->sectors = NULL;
    NumSectors = 0;
}

/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
static void vline(int x, int y1,int y2, int top,int middle,int bottom, SDL_Surface* surface)
{
    int	*pix;

	pix = (int*)surface->pixels;
    y1 = clamp(y1, 0, WIN_H - 1);
    y2 = clamp(y2, 0, WIN_H - 1);
    if(y2 == y1)
        pix[y1* WIN_W + x] = middle;
    else if(y2 > y1)
    {
        pix[y1 * WIN_W + x] = top;
        for(int y= y1 + 1; y < y2; ++y)
            pix[y * WIN_W + x] = middle;
        pix[y2 * WIN_W + x] = bottom;
    }
}
/* MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
 * also updates their anglesin/anglecos/sector properties properly.
 */
void MovePlayer(float dx, float dy, t_player *pl)
{
    float px = pl->where.x;
    float py = pl->where.y;
    /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, PointSide will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    const t_sector * const sect = &pl->sectors[pl->sector];
    const t_xy* const vert = sect->vertex;
    for(unsigned s = 0; s < sect->npoints; ++s)
        if(sect->neighbors[s] >= 0
           && IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
           && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
        {
            pl->sector = sect->neighbors[s];
            break;
        }

    pl->where.x += dx;
    pl->where.y += dy;
    pl->anglesin = sinf(pl->angle);
    pl->anglecos = cosf(pl->angle);
}

void DrawScreen(t_player *pl, SDL_Surface *surface)
{
	/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */

	/* Rotate them around the player's view */
	/*float tx1 = 0;
	float tz1 = 0;
	float tx2 = 0;
	float tz2 = 0;
	t_xy i1 = {0,0};
	t_xy i2 = {0,0};*/
	int neighbor;
	/* Render the wall. */
	int beginx;
	int endx;
	int x;
	/* Calculate the Z coordinate for this point. (Only used for lighting.) */
	int z;

	enum { MaxQueue = 32 };  // maximum number of pending portal renders
	struct item { int sectorno, sx1, sx2; } queue[MaxQueue], *head = queue, *tail = queue;
	int ytop[WIN_W] = { 0 };
	int ybottom[WIN_W];
	int renderedsectors[NumSectors];
	for(unsigned x = 0; x < WIN_W; ++x) ybottom[x] = WIN_H - 1;
	for(unsigned n = 0; n < NumSectors; ++n) renderedsectors[n] = 0;

	/* Begin whole-screen rendering from where the player is. */
	*head = (struct item) { pl->sector, 0, WIN_W-1 };
	if(++head == queue + MaxQueue) head = queue;

    do {
        /* Pick a sector & slice from the queue to draw */
        const struct item now = *tail;
        if(++tail == queue + MaxQueue) tail = queue;

        if(renderedsectors[now.sectorno] & 0x21) continue; // Odd = still rendering, 0x20 = give up
        ++renderedsectors[now.sectorno];
        const t_sector* const sect = &pl->sectors[now.sectorno];//SECT CREATED
        /* Render each wall of this sector that is facing towards player. */
        for(unsigned s = 0; s < sect->npoints; ++s)
        {
			// Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector
			/*v_start.x = sect->vertex[s + 0].x - pl->where.x;
			v_start.y = sect->vertex[s + 0].y - pl->where.y;
			v_end.x = sect->vertex[s + 1].x - pl->where.x;
			v_end.y = sect->vertex[s + 1].y - pl->where.y;*/
			if (engine_cross(pl, now.sectorno, s) == 0)
				continue;
			/* Acquire the floor and ceiling heights, relative to where the player's view is */
			pl->ceil.yceil = sect->ceil - pl->where.z;
			pl->floor.yfloor = sect->floor - pl->where.z;
			/* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
			neighbor = sect->neighbors[s];
			if(neighbor >= 0) // Is another sector showing through this portal? This permit us draw other sectors after the one where we are
			{
				pl->ceil.nyceil  = pl->sectors[neighbor].ceil  - pl->where.z;
				pl->floor.nyfloor = pl->sectors[neighbor].floor - pl->where.z;
			}
			/* Project ceiling & floor heights into screen coordinates (Y coordinate) */
			engine_scale(pl, pl->t1.y, pl->t2.y);
			/* Do perspective transformation */
			pl->x1 = WIN_W / 2 - (int)(pl->t1.x * pl->scale_1.x);
			pl->x2 = WIN_W / 2 - (int)(pl->t2.x * pl->scale_2.x);
			if(pl->x1 >= pl->x2 || pl->x2 < now.sx1 || pl->x1 > now.sx2) continue; // Only render if it's visible
			/* Render the wall. */
			beginx = max(pl->x1, now.sx1);
			endx = min(pl->x2, now.sx2);
			for(x = beginx; x <= endx; ++x)
			{
				/* Calculate the Z coordinate for this point. (Only used for lighting.) */
				z = ((x - pl->x1) * (pl->t2.y - pl->t1.y) / (pl->x2 - pl->x1) + pl->t1.y) * 8;
				/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
				pl->floor.ya = (x - pl->x1) * (pl->ceil.y2a - pl->ceil.y1a) / (pl->x2 - pl->x1) + pl->ceil.y1a;
				pl->ceil.cya = clamp(pl->floor.ya, ytop[x],ybottom[x]); // top
				pl->floor.yb = (x - pl->x1) * (pl->floor.y2b - pl->floor.y1b) / (pl->x2 - pl->x1) + pl->floor.y1b;
				pl->ceil.cyb = clamp(pl->floor.yb, ytop[x],ybottom[x]); // bottom
				/* Render ceiling: everything above this sector's ceiling height. */
				vline(x, ytop[x], pl->ceil.cya - 1, 0xffffff, 0x222222 , 0xff0000, surface);//ceiling colors
				/* Render floor: everything below this sector's floor height. */
				vline(x, pl->ceil.cyb + 1, ybottom[x], 0x00ff00, 0x0000AA, 0x0000FF, surface);//floor colors
				/* Is there another sector behind this edge? */
				if(neighbor >= 0)
                {
                    /* Same for _their_ floor and ceiling */
                    pl->floor.nya = (x - pl->x1) * (pl->ceil.ny2a - pl->ceil.ny1a) / (pl->x2 - pl->x1) + pl->ceil.ny1a;
                    pl->ceil.cnya = clamp(pl->floor.nya, ytop[x], ybottom[x]);
					pl->floor.nyb = (x - pl->x1) * (pl->floor.ny2b - pl->floor.ny1b) / (pl->x2 - pl->x1) + pl->floor.ny1b;
                    pl->ceil.cnyb = clamp(pl->floor.nyb, ytop[x], ybottom[x]);
                    /* If our ceiling is higher than their ceiling, render upper wall */
                    unsigned r1 = 0xff0000 * (255 - z ), r2 = 0x00ff00 * (31 - z / 8);//wall colors
                    vline(x, pl->ceil.cya, pl->ceil.cnya - 1, 0, (x == pl->x1) || (x == pl->x2) ? 0 : r1, 0, surface); // Between our and their ceiling
                    ytop[x] = clamp(max(pl->ceil.cya, pl->ceil.cnya), ytop[x], WIN_H-1);   // Shrink the remaining window below these ceilings
                    /* If our floor is lower than their floor, render bottom wall */
                    vline(x, pl->ceil.cnyb+1, pl->ceil.cyb, 0, (x == pl->x1) || (x == pl->x2) ? 0 : r2, 0, surface); // Between their and our floor
                    ybottom[x] = clamp(min(pl->ceil.cyb, pl->ceil.cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
                }
                else
                {
                    /* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
                    unsigned r = 0x0000ff * (255 - z);
                    vline(x, pl->ceil.cya, pl->ceil.cyb, 0, (x == pl->x1) || (x == pl->x2) ? 0 : r, 0, surface);
                }
            }
            /* Schedule the neighboring sector for rendering within the window formed by this wall. */
            if(neighbor >= 0 && endx >= beginx && (head + MaxQueue + 1 - tail) % MaxQueue)
            {
                *head = (struct item) { neighbor, beginx, endx};
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
    t_player pl;
    t_others ot;
    t_sector_ops op;
	t_wolf3d w;
	//SDL_Texture *texture = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface* surface = NULL;

    w.weapon_texture = SDL_LoadBMP("Textures/pistol.bmp");
    if (ac < 2 || ac > 2)
    {
        printf("map error");
        return (0);
    }
    se.quit = 0;
    LoadData(ag[1], &pl);//load map and init typedef t_player data
    //ft_init_anim(&w);//gun
    SDL_Window* window = NULL;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN );

        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
            {
            surface = SDL_GetWindowSurface(window);
            SDL_UpdateWindowSurface( window );
            renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED );
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
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

                //texture = SDL_CreateTextureFromSurface(renderer, surface);

                //SDL_FreeSurface(surface);
                //Clear screen
                //SDL_RenderClear(renderer);
                //Render texture to screen
                //SDL_RenderCopy(renderer, texture, NULL, NULL );
                //Update screen
                //for( int i = 0; i < H; i += 1 )
               // {
                //    SDL_RenderDrawPoint( renderer, W / 2, i );
                //}
                //SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
                //SDL_RenderPresent(renderer);
                DrawScreen(&pl, surface);
                //ft_animation_play(&w);
                //ft_draw_animation(&w, surface);
                SDL_UpdateWindowSurface( window );
                /* Vertical collision detection */
                op.eyeheight = se.ducking ? DuckHeight : EyeHeight;
                se.ground = !se.falling;
                jumps(&se, &pl, &op, &ot);
                sectors_ops(&op, &pl, &ot, &se);
                if (!events(&se, &pl))
                    return(0);
                mouse_movement(&ms, &pl);/* mouse aiming */
                vectors_vel_dir(&pl, &se, &ot);
                MovePlayer(0, 0, &pl);//Refresh Vectors. start movement in 0//if this line is in vectors_vel_dir slomaet programmy whe is running, is needed here
            }
            UnloadData(&pl);
            SDL_Quit();
        }
    }
    return 0;
}