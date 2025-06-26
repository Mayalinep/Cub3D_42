/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:36:47 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/26 16:32:53 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "cub3d.h"

void	calculate_ray_direction(int x, t_game *game, double *ray_dir_x,
		double *ray_dir_y)
{
	double	camera_x;

	if (x < 0 || x >= SCREEN_WIDTH)
		return ;
	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	*ray_dir_x = game->parsed_data.dir_x + game->parsed_data.plane_x * camera_x;
	*ray_dir_y = game->parsed_data.dir_y + game->parsed_data.plane_y * camera_x;
}

double	find_wall_distance(double ray_dir_x, double ray_dir_y, t_game *game)
{
	double	distance;

	game->raycasting.map_x = (int)game->parsed_data.player_x;
	game->raycasting.map_y = (int)game->parsed_data.player_y;
	game->raycasting.delta_dist_x = calculate_delta_dist_x(ray_dir_x);
	game->raycasting.delta_dist_y = calculate_delta_dist_y(ray_dir_y);
	ray_orientation(ray_dir_x, ray_dir_y, &game->raycasting.step_x,
		&game->raycasting.step_y);
	if (game->raycasting.step_x == -1)
		game->raycasting.side_dist_x = (game->parsed_data.player_x
				- game->raycasting.map_x) * game->raycasting.delta_dist_x;
	else
		game->raycasting.side_dist_x = (game->raycasting.map_x + 1.0
				- game->parsed_data.player_x) * game->raycasting.delta_dist_x;
	if (game->raycasting.step_y == -1)
		game->raycasting.side_dist_y = (game->parsed_data.player_y
				- game->raycasting.map_y) * game->raycasting.delta_dist_y;
	else
		game->raycasting.side_dist_y = (game->raycasting.map_y + 1.0
				- game->parsed_data.player_y) * game->raycasting.delta_dist_y;
	dda_loop(game);
	distance = calculate_final_distance(ray_dir_x, ray_dir_y, game);
	calculate_wall_x(ray_dir_x, ray_dir_y, distance, game);
	return (distance);
}

int	calculate_line_height(double distance)
{
	int	line_height;

	if (distance <= 0)
		return (SCREEN_HEIGHT);
	line_height = (int)(SCREEN_HEIGHT / distance);
	if (line_height > SCREEN_HEIGHT)
		line_height = SCREEN_HEIGHT;
	return (line_height);
}

int	ray_casting(t_game *game)
{
	int		x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	distance;
	int		line_height;

	if (!game)
		return (-1);
	
	// Dessiner le sol et le ciel en premier
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
	
	// Dessiner la mini-map par-dessus
	draw_minimap(game);
	
	return (0);
}
