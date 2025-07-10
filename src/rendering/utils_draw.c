/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:11:20 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/10 14:32:48 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	char	*pixel;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	pixel = game->mlx_data.addr + (y * game->mlx_data.line_length + x
			* (game->mlx_data.bits_per_pixel / 8));
	*(int *)pixel = color;
}

int	get_wall_color(t_raycasting *ray)
{
	int	color_index;

	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			color_index = 1;
		else
			color_index = 0;
	}
	else
	{
		if (ray->step_y > 0)
			color_index = 3;
		else
			color_index = 2;
	}
	if (color_index == 0)
		return (WALL_WEST_COLOR);
	else if (color_index == 1)
		return (WALL_EAST_COLOR);
	else if (color_index == 2)
		return (WALL_NORTH_COLOR);
	else
		return (WALL_SOUTH_COLOR);
}

int	get_texture_index(t_raycasting *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->step_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

int	create_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

t_range	calculate_draw_range(int line_height)
{
	t_range	range;

	range.start = -line_height / 2 + SCREEN_HEIGHT / 2;
	range.end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (range.start < 0)
		range.start = 0;
	if (range.end >= SCREEN_HEIGHT)
		range.end = SCREEN_HEIGHT - 1;
	return (range);
}
