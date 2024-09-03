/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juguerre <juguerre@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:50:29 by regea-go          #+#    #+#             */
/*   Updated: 2024/09/03 03:27:01 by juguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_pixel_raycast(t_game *game, double x, double y)
{
    double x_window;
    double y_window;

    x_window = x * game->x_scale_minimap;
    y_window = y * game->y_scale_minimap;
    if (x_window < MINIMAP_WIDTH && x_window > 0 && y_window < MINIMAP_HEIGHT && y_window > 0)
        mlx_put_pixel(game->img, x_window, y_window, PLUM);
}

void draw_player_minimap(t_game *game) 
{
    int player_x;
    int player_y;
    
    player_x = (int)(game->player->x_pos * game->x_scale_minimap);
    player_y = (int)(game->player->y_pos * game->y_scale_minimap);
    if (player_x >= 0 && player_x < MINIMAP_WIDTH && player_y >= 0 && player_y < MINIMAP_HEIGHT)
        draw_square_minimap(game, player_x, player_y);
}

void render_screen(t_game *game)
{
    fill_background_3d(game);
    fill_background_minimap(game);
    point_of_view(game);
    draw_player_minimap(game);
    mlx_image_to_window(game->mlx, game->img, 0, 0); 
}

