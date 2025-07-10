/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:15:12 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/10 14:42:51 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"

void	draw_floor_and_ceiling(t_game *game)
{
	int	y;
	int	floor_color;
	int	ceiling_color;

	floor_color = create_rgb_color(game->parsed_data.floor_r,
			game->parsed_data.floor_g, game->parsed_data.floor_b);
	ceiling_color = create_rgb_color(game->parsed_data.ceiling_r,
			game->parsed_data.ceiling_g, game->parsed_data.ceiling_b);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		if (y < SCREEN_HEIGHT / 2)
			draw_horizontal_line((t_range){0, SCREEN_WIDTH - 1}, y,
				ceiling_color, game);
		else
			draw_horizontal_line((t_range){0, SCREEN_WIDTH - 1}, y, floor_color,
				game);
		y++;
	}
}
