/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juguerre <juguerre@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:49:52 by regea-go          #+#    #+#             */
/*   Updated: 2024/09/03 03:40:55 by juguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void fill_background_3d(t_game *game)
{
    draw_ceiling_3d(game);
    draw_floor_3d(game);
}

static void draw_orientation_3d(t_game *game, int x_comp, double y_comp, int wall)
{
    if (wall == WEST)
        mlx_put_pixel(game->img, x_comp, y_comp, DARK_BLUE);
    else if (wall == EAST)
        mlx_put_pixel(game->img, x_comp, y_comp, VIOLET);
    else if (wall == NORTH)
        mlx_put_pixel(game->img, x_comp, y_comp, DARK_MAGENTA);
    else if (wall == SOUTH)         
        mlx_put_pixel(game->img, x_comp, y_comp, SKY_BLUE);
}

static void draw_columns_per_coordinate_3d(t_game *game, double wall_height, double offset_x, int wall)
{
    double y_start;
    double y_end;
    double rays;

    rays = 0.0;
    while (rays < COLUMNS_PER_RAY)
    {
        y_start = (int)(HEIGHT / 2.0 - wall_height / 2.0);
        y_end = (int)(HEIGHT / 2.0 + wall_height / 2.0);

        if(y_start < 0)                                           
            y_start = 0;
        if(y_end > HEIGHT)
            y_end = HEIGHT;                                                            
        while (y_start < y_end)
            draw_orientation_3d(game, round(rays + offset_x), y_start++, wall);
        rays += 1.0;
    }
}

void render_obstacle_3d(t_game *game, int iteration, double distance, int wall)
{
    int offset_x;
    double wall_height;

    offset_x = (iteration * COLUMNS_PER_RAY);
    wall_height = MAX_WALL_HEIGHT / (distance / 2);
    draw_columns_per_coordinate_3d(game, wall_height, offset_x, wall);
}

void single_raycast_to_3d(t_game *game, double x, double y, int iteration)
{
    double distance;
    double decimal_x;
    double decimal_y;

    distance = sqrt(pow(x - game->player->x_pos, 2) + pow(y - game->player->y_pos, 2));
    decimal_x = x - round(x);
    decimal_y = y - round(y);

    if (abs_min(decimal_x, decimal_y) == fabs(decimal_x)                        // Touching X axis and facing West
        && decimal_x > 0)                    
        render_obstacle_3d(game, iteration, distance, WEST);
    else if (abs_min(decimal_x, decimal_y) == fabs(decimal_x)                   // Touching X axis and facing East (negative X)
        && decimal_x < 0)               
        render_obstacle_3d(game, iteration, distance, EAST);        
    else if (abs_min(decimal_x, decimal_y) == fabs(decimal_y)                   // Touching Y axis and facing North
        && decimal_y > 0)                                                       
        render_obstacle_3d(game, iteration, distance, NORTH);
    else if (abs_min(decimal_x, decimal_y) == fabs(decimal_y)                   // Touching Y axis and facing South
        && decimal_y < 0)                                                       
        render_obstacle_3d(game, iteration, distance, SOUTH);
}