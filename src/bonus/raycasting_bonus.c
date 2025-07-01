/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:55:00 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/01 18:03:05 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"

int	ray_casting_bonus(t_game *game)
{
	int		x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	distance;
	int		line_height;

	if (!game)
		return (-1);
	draw_floor_and_ceiling(game);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		calculate_ray_direction(x, game, &ray_dir_x, &ray_dir_y);
		distance = find_wall_distance(ray_dir_x, ray_dir_y, game);
		line_height = calculate_line_height(distance);
		draw_vertical_line(x, line_height, game);
		x++;
	}
	draw_minimap(game);
	return (0);
} 