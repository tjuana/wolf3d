//
// Created by Nymphadora Shelly on 19/12/2019.
//
#include "prender.h"

int sub_events(t_subevents *se, t_player *player)
{
    if (se->ev.key.keysym.sym == 'w')
        se->wsad[0] = se->ev.type == SDL_KEYDOWN;
    if (se->ev.key.keysym.sym == 's')
        se->wsad[1] = se->ev.type == SDL_KEYDOWN;
    if (se->ev.key.keysym.sym == 'a')
        se->wsad[2] = se->ev.type == SDL_KEYDOWN;
    if (se->ev.key.keysym.sym == 'd')
        se->wsad[3] = se->ev.type == SDL_KEYDOWN;
    if (se->ev.key.keysym.sym == SDLK_ESCAPE)//quit
    {
        UnloadData(player);
        SDL_Quit();
        return (0);
    }
    if (se->ev.key.keysym.sym == ' ')//jump
        if (se->ground)
        {
            player->velocity.z += 0.5;
            se->falling = 1;
        }
    if (se->ev.key.keysym.sym == SDLK_LCTRL)//crouch
    {
        se->ducking = se->ev.type == SDL_KEYDOWN;
        se->falling = 1;
    }
    return(1);
}

int events(t_subevents *se, t_player *player)//inside of this function is sub_events function, we add t_player because is neede by sub_events for jump
{
    while (SDL_PollEvent(&se->ev))
    {
        if (se->ev.type == SDL_QUIT)
            se->quit = 1;
        if (se->ev.type)
        {
            if(se->ev.type == SDL_KEYDOWN || se->ev.type == SDL_KEYUP)//esto solo sucede al presionar y al soltar
            {
                if (se->ev.key.keysym.sym)
                    if(!sub_events(se, player))//KEYS//here we dont have to put * because we already are giving a pointer
                        return(0);
                if(se->ev.type == SDL_QUIT)
                {
                    UnloadData(player);
                    SDL_Quit();
                    return (0);
                }
            }
        }
    }
    return(1);
}

void mouse_movement(t_mouse *ms, t_player *player)
{
    SDL_GetRelativeMouseState(&ms->x, &ms->y);
    player->angle += ms->x * 0.03f;//mouse left-right
    ms->yaw = clamp(ms->yaw - ms->y * 0.05f, -5, 5);//mouse up-down
    player->yaw = ms->yaw - player->velocity.z * 0.5f;
}

void vectors_vel_dir(t_player *player, t_subevents *se, t_others *ot)//for flying
{

    ot->move_vec[0] = 0.f;//direction in x
    ot->move_vec[1] = 0.f;//direction in y
    if (se->wsad[0])
    {
        ot->move_vec[0] += player->anglecos * 0.2f;
        ot->move_vec[1] += player->anglesin * 0.2f;
    }
    if (se->wsad[1])
    {
        ot->move_vec[0] -= player->anglecos * 0.2f;
        ot->move_vec[1] -= player->anglesin * 0.2f;
    }
    if (se->wsad[2])
    {
        ot->move_vec[0] += player->anglesin * 0.2f;
        ot->move_vec[1] -= player->anglecos * 0.2f;
    }
    if (se->wsad[3])
    {
        ot->move_vec[0] -= player->anglesin * 0.2f;
        ot->move_vec[1] += player->anglecos * 0.2f;
    }
    int pushing = se->wsad[0] || se->wsad[1] || se->wsad[2] || se->wsad[3];
    float acceleration = pushing ? 0.4 : 0.2;
    player->velocity.x = player->velocity.x * (1 - acceleration) + ot->move_vec[0] * acceleration;
    player->velocity.y = player->velocity.y * (1 - acceleration) + ot->move_vec[1] * acceleration;
    if (pushing)
        ot->moving = 1;
}

void sectors_ops(t_sector_ops *op, t_player *player, t_others *ot, t_subevents *se)//operations with sectors
{
    if (ot->moving)
    {
        op->px = player->where.x;
        op->py = player->where.y;
        op->dx = player->velocity.x;
        op->dy = player->velocity.y;

        op->sect = &player->sectors[player->sector];
        op->vert = op->sect->vertex;
        /* Check if the player is about to cross one of the sector's edges */
        for (unsigned s = 0; s < op->sect->npoints; ++s)
            if (IntersectBox(op->px, op->py, op->px + op->dx, op->py + op->dy, op->vert[s + 0].x, op->vert[s + 0].y, op->vert[s + 1].x,op->vert[s + 1].y) \
                        && PointSide(op->px + op->dx, op->py + op->dy, op->vert[s + 0].x, op->vert[s + 0].y, op->vert[s + 1].x, op->vert[s + 1].y) < 0)
            {
                /* Check where the hole is. */
                op->hole_low = op->sect->neighbors[s] < 0 ? 9e9 : max(op->sect->floor, player->sectors[op->sect->neighbors[s]].floor);
                op->hole_high = op->sect->neighbors[s] < 0 ? -9e9 : min(op->sect->ceil, player->sectors[op->sect->neighbors[s]].ceil);
                /* Check whether we're bumping into a wall. */
                if (op->hole_high < player->where.z + HeadMargin || op->hole_low > player->where.z - op->eyeheight + KneeHeight)
                {
                    /* Bumps into a wall! Slide along the wall. */
                    /* This formula is from Wikipedia article "vector projection". */
                    op->xd = op->vert[s + 1].x - op->vert[s + 0].x;
                    op->yd = op->vert[s + 1].y - op->vert[s + 0].y;
                    op->dx = op->xd * (op->dx * op->xd + op->yd * op->dy) / (op->xd * op->xd + op->yd * op->yd);
                    op->dy = op->yd * (op->dx * op->xd + op->yd * op->dy) / (op->xd * op->xd + op->yd * op->yd);
                    ot->moving = 0;
                }
            }
        MovePlayer(op->dx, op->dy, player);//MOVES WASD, mouse aiming dont depend of this
        se->falling = 1;
    }
}

void jumps(t_subevents *se, t_player *player, t_sector_ops *op, t_others *ot)
{
    if (se->falling)
    {
        player->velocity.z -= 0.015f; /* Add gravity */
        float nextz = player->where.z + player->velocity.z;
        if (player->velocity.z < 0 && nextz < player->sectors[player->sector].floor + op->eyeheight) // When going down
        {
            /* Fix to ground */
            player->where.z = player->sectors[player->sector].floor + op->eyeheight;
            player->velocity.z = 0;
            se->falling = 0;
            se->ground = 1;
        } else if (player->velocity.z > 0 && nextz > player->sectors[player->sector].ceil) // When going up
        {
            /* Prevent jumping above ceiling */
            player->velocity.z = 0;
            se->falling = 1;
        }
        if (se->falling) {
            player->where.z += player->velocity.z;
            ot->moving = 1;
        }
    }
}
