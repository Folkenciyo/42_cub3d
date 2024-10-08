/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_projection_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:50:18 by regea-go          #+#    #+#             */
/*   Updated: 2024/08/31 21:50:19 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	rgb_to_hex(char *str)
{
	int	rgb[3];
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (!ft_isdigit(str[i]))
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
		{
			rgb[j] = ft_atoi(&str[i]);
			j++;
			while (ft_isdigit(str[i]))
				i++;
		}
		else
			i++;
	}
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 0x000000FF);
}

double	abs_min(double a, double b)
{
	if (fabs(a) < fabs(b))
		return (fabs(a));
	return (fabs(b));
}

double	ft_distance(t_game *game, double x, double y)
{
	double	x_pos;
	double	y_pos;
	double	dist;

	x_pos = game->player->x_pos;
	y_pos = game->player->y_pos;
	dist = sqrt(pow(x - x_pos, 2) + pow(y - y_pos, 2));
	return (dist);
}

void	draw_ceiling_3d(t_game *game)
{
	int			y;
	int			x;
	uint32_t	color;

	y = 0;
	x = 0;
	color = rgb_to_hex(game->data->texture[5]);
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
			mlx_put_pixel(game->img, x++, y, color);
		y++;
	}
}

void	draw_floor_3d(t_game *game)
{
	int			y;
	int			x;
	uint32_t	color;

	y = HEIGHT / 2;
	x = 0;
	color = rgb_to_hex(game->data->texture[4]);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			mlx_put_pixel(game->img, x++, y, color);
		y++;
	}
}
