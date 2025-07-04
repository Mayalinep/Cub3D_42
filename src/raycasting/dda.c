/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:36:35 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/04 22:42:17 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_loop(t_game *game)
{
	int	map_x;
	int	map_y;
	int	max_x;
	int	max_y;

	game->raycasting.hit = 0;
	map_x = game->raycasting.map_x;
	map_y = game->raycasting.map_y;
	max_x = game->parsed_data.map_width - 1;
	max_y = game->parsed_data.map_height - 1;
	while (game->raycasting.hit == 0)
	{
		if (game->raycasting.side_dist_x < game->raycasting.side_dist_y)
		{
			game->raycasting.side_dist_x += game->raycasting.delta_dist_x;
			map_x += game->raycasting.step_x;
			game->raycasting.side = 0;
		}
		else
		{
			game->raycasting.side_dist_y += game->raycasting.delta_dist_y;
			map_y += game->raycasting.step_y;
			game->raycasting.side = 1;
		}
		if (map_x < 0 || map_x > max_x || map_y < 0 || map_y > max_y)
		{
			game->raycasting.hit = 1;
			return ;
		}
		if (game->parsed_data.map[map_y][map_x] == '1')
			game->raycasting.hit = 1;
	}
	game->raycasting.map_x = map_x;
	game->raycasting.map_y = map_y;
}

double	calculate_final_distance(double ray_dir_x, double ray_dir_y,
		t_game *game)
{
	double	perp_wall_dist;

	if (game->raycasting.side == 0)
	{
		// Mur vertical (Est ou Ouest)
		perp_wall_dist = (game->raycasting.map_x - game->parsed_data.player_x
				+ (1 - game->raycasting.step_x) / 2.0) / ray_dir_x;
	}
	else
	{
		// Mur horizontal (Nord ou Sud)
		perp_wall_dist = (game->raycasting.map_y - game->parsed_data.player_y
				+ (1 - game->raycasting.step_y) / 2.0) / ray_dir_y;
	}
	// S'assurer que la distance est positive et pas trop petite
	if (perp_wall_dist < 0)
		perp_wall_dist = -perp_wall_dist;
	if (perp_wall_dist < 0.2)
		perp_wall_dist = 0.2;
	return (perp_wall_dist);
}
