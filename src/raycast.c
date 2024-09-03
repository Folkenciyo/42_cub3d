/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juguerre <juguerre@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:50:45 by regea-go          #+#    #+#             */
/*   Updated: 2024/09/03 03:30:19 by juguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int raycast_iteration(t_game *game, double x1, double y1, int iteration)
{
    double i;
    double x;
    double y;

    i = 0;
    while (i < VISION_LENGTH)
    {
        x = (double)(game->player->x_pos + i * (x1 - game->player->x_pos) / VISION_LENGTH);
        y = (double)(game->player->y_pos + i * (y1 - game->player->y_pos) / VISION_LENGTH);
        put_pixel_raycast(game, x, y);
        if (game->data->map2d_square[(int)y][(int)x] == WALL)
        {
            single_raycast_to_3d(game, x, y, iteration);
            return (TRUE);
        }
        i += RAY_CALCULATION_RATE;
    }
    return (FALSE);
}
//Raycasting algorithm; right now it is just a brute force algorithm
int raycast_algorithm(t_game *game, double angle, int iteration)
{
    double x1;
    double y1;

    x1 = game->player->x_pos + VISION_LENGTH * cos(angle);
    y1 = game->player->y_pos + VISION_LENGTH * sin(angle);
    return (raycast_iteration(game, x1, y1, iteration));
}

void point_of_view(t_game *game) {
    
    double angle_step;
    double start_angle;
    double current_angle;
    int i;
    
    angle_step = FOV_ANGLE / NUM_RAYS;
    start_angle = game->player->angle - FOV_ANGLE / 2.0;
    i = 0;
    while (i < NUM_RAYS)
    {
        current_angle = start_angle + i * angle_step;
        raycast_algorithm(game, current_angle, i);
        i++;
    }
}