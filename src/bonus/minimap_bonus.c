/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 22:49:06 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/10 11:00:53 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_square(int map_x, int map_y, int color, t_game *game)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;
	int	scale;
	int	offset_x;
	int	offset_y;

	scale = 8;
	offset_x = SCREEN_WIDTH - (game->parsed_data.map_width * scale) - 20;
	offset_y = 20;
	screen_x = map_x * scale + offset_x;
	screen_y = map_y * scale + offset_y;
	y = 0;
	while (y < scale)
	{
		x = 0;
		while (x < scale)
		{
			put_pixel(screen_x + x, screen_y + y, color, game);
			x++;
		}
		y++;
	}
}

void	draw_minimap_walls(t_game *game)
{
	int	x;
	int	y;
	int	line_len;

	y = 0;
	while (y < game->parsed_data.map_height)
	{
		if (game->parsed_data.map[y])
		{
			line_len = ft_strlen(game->parsed_data.map[y]);
			x = 0;
			while (x < game->parsed_data.map_width)
			{
				if (x < line_len && game->parsed_data.map[y][x] == '1')
					draw_minimap_square(x, y, 0x404040, game);
				else
					draw_minimap_square(x, y, 0x202020, game);
				x++;
			}
		}
		y++;
	}
}

void	draw_minimap_player(t_game *game)
{
	int	player_x;
	int	player_y;
	int	x;
	int	y;

	player_x = (int)(game->parsed_data.player_x * 8) + (SCREEN_WIDTH
			- (game->parsed_data.map_width * 8) - 20);
	player_y = (int)(game->parsed_data.player_y * 8) + 20;
	y = -2;
	while (y <= 2)
	{
		x = -2;
		while (x <= 2)
		{
			put_pixel(player_x + x, player_y + y, 0xFF0000, game);
			x++;
		}
		y++;
	}
}

void	draw_minimap_direction(t_game *game)
{
	int	x;
	int	y;
	int	player_x;
	int	player_y;
	int	i;

	player_x = (int)(game->parsed_data.player_x * 8) + (SCREEN_WIDTH
			- (game->parsed_data.map_width * 8) - 20);
	player_y = (int)(game->parsed_data.player_y * 8) + 20;
	i = 0;
	while (i < 10)
	{
		x = player_x + (int)(game->parsed_data.dir_x * i);
		y = player_y + (int)(game->parsed_data.dir_y * i);
		put_pixel(x, y, 0xFF00FF, game);
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	draw_minimap_walls(game);
	draw_minimap_player(game);
	draw_minimap_direction(game);
}
