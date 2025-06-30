/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:36:35 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/30 14:31:29 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_loop(t_game *game)
{
	game->raycasting.hit = 0;
	while (game->raycasting.hit == 0)
	{
		if (game->raycasting.side_dist_x < game->raycasting.side_dist_y)
		{
			game->raycasting.side_dist_x += game->raycasting.delta_dist_x;
			game->raycasting.map_x += game->raycasting.step_x;
			game->raycasting.side = 0;
		}
		else
		{
			game->raycasting.side_dist_y += game->raycasting.delta_dist_y;
			game->raycasting.map_y += game->raycasting.step_y;
			game->raycasting.side = 1;
		}
		if (game->raycasting.map_x < 0
			|| game->raycasting.map_x >= game->parsed_data.map_width
			|| game->raycasting.map_y < 0
			|| game->raycasting.map_y >= game->parsed_data.map_height)
		{
			game->raycasting.hit = 1;
			return ;
		}
		if (game->parsed_data.map[game->raycasting.map_y][game->raycasting.map_x] == '1')
			game->raycasting.hit = 1;
	}
}

double	calculate_final_distance(double ray_dir_x, double ray_dir_y,
		t_game *game)
{
	double	distance;

	if (game->raycasting.side == 0)
		distance = (game->raycasting.map_x - game->parsed_data.player_x + (1
					- game->raycasting.step_x) / 2) / ray_dir_x;
	else
		distance = (game->raycasting.map_y - game->parsed_data.player_y + (1
					- game->raycasting.step_y) / 2) / ray_dir_y;
	
	// S'assurer que la distance est positive et pas trop petite
	if (distance < 0)
		distance = -distance;
	if (distance < 0.3)
		distance = 0.3;
	
	return (distance);
}
