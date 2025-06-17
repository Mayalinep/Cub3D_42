/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:36:47 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/17 18:03:53 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void calculate_ray_direction(int x, t_game *game, double *ray_dir_x, double *ray_dir_y)
{
    double camera_x;
    camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
    *ray_dir_x = game->parsed_data.dir_x + game->parsed_data.plane_x * camera_x;
    *ray_dir_y = game->parsed_data.dir_y + game->parsed_data.plane_y * camera_x;
}

double find_wall_distance(double ray_dir_x, double ray_dir_y, t_game *game)
{
    return (0);
}

int calculate_line_height(double distance)
{
    return (0);
}

int ray_casting(t_game *game)
{
    int x;
    double ray_dir_x;
    double ray_dir_y;
    double distance;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        calculate_ray_direction(x, game, &ray_dir_x, &ray_dir_y);
        distance = find_wall_distance(ray_dir_x, ray_dir_y, game);
        calculate_line_height(distance);
        x++;
    }
    return (0);
}