/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:03:33 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/10 11:18:25 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_delta_dist_x(double ray_dir_x)
{
	if (ray_dir_x == 0.0)
		return (1e30);
	return (fabs(1.0 / ray_dir_x));
}

double	calculate_delta_dist_y(double ray_dir_y)
{
	if (ray_dir_y == 0.0)
		return (1e30);
	return (fabs(1.0 / ray_dir_y));
}

void	ray_orientation(double ray_dir_x, double ray_dir_y, int *step_x,
		int *step_y)
{
	if (ray_dir_x < 0)
		*step_x = -1;
	else
		*step_x = 1;
	if (ray_dir_y < 0)
		*step_y = -1;
	else
		*step_y = 1;
}

void	calculate_wall_x(double ray_dir_x, double ray_dir_y, double distance,
		t_game *game)
{
	double	wall_x;

	if (game->raycasting.side == 1)
		wall_x = game->parsed_data.player_x + distance * ray_dir_x;
	else
		wall_x = game->parsed_data.player_y + distance * ray_dir_y;
	wall_x -= floor(wall_x);
	game->raycasting.wall_x = wall_x;
}
