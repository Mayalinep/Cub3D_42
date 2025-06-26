/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:53:34 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/26 15:07:46 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	char	*pixel;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	pixel = game->mlx_data.addr + (y * game->mlx_data.line_length + 
			x * (game->mlx_data.bits_per_pixel / 8));
	*(int*)pixel = color;
}

int	get_wall_color(t_raycasting *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (WALL_EAST_COLOR);
		else
			return (WALL_WEST_COLOR);
	}
	else
	{
		if (ray->step_y > 0)
			return (WALL_SOUTH_COLOR);
		else
			return (WALL_NORTH_COLOR);
	}
}

void	draw_vertical_line_color(int x, int line_height, t_game *game)
{
	int	draw_start;
	int	draw_end;
	int	color;
	int	y;

	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	color = get_wall_color(&game->raycasting);
	y = draw_start;
	while (y <= draw_end)
	{
		put_pixel(x, y, color, game);
		y++;
	}
}

void	draw_vertical_line_texture(int x, int line_height, t_game *game)
{
	// TODO: Implémenter le rendu avec textures
	// Pour l'instant, on utilise les couleurs
	draw_vertical_line_color(x, line_height, game);
}

void	draw_vertical_line(int x, int line_height, t_game *game)
{
	// Pour l'instant, on utilise toujours les couleurs
	draw_vertical_line_color(x, line_height, game);
}

