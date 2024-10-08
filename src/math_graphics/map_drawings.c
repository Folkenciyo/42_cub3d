/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:50:29 by regea-go          #+#    #+#             */
/*   Updated: 2024/08/31 21:50:30 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_ray_minimap(t_game *game, double x, double y)
{
	double	x_window;
	double	y_window;

	x_window = x * game->x_scale_minimap;
	y_window = y * game->y_scale_minimap;
	if (x_window < MINIMAP_WIDTH && x_window > 0
		&& y_window < MINIMAP_HEIGHT && y_window > 0)
		mlx_put_pixel(game->img, x_window, y_window, VISION_MINIMAP);
}

void	render_screen(t_game *game)
{
	fill_background_3d(game);
	point_of_view(game);
	draw_minimap(game);
	draw_player_minimap(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}
