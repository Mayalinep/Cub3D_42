/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:53:34 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/10 14:30:56 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"

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

int	calculate_texture_coords(t_game *game, int *texture_index)
{
	int	tex_x;

	*texture_index = get_texture_index(&game->raycasting);
	tex_x = (int)(game->raycasting.wall_x * 64);
	if ((game->raycasting.side == 0 && game->raycasting.step_x < 0)
		|| (game->raycasting.side == 1 && game->raycasting.step_y > 0))
		tex_x = 64 - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x > 63)
		tex_x = 63;
	return (tex_x);
}

void	draw_vertical_line_texture(int x, int line_height, t_game *game)
{
	t_range			range;
	t_texture_data	tex_data;
	int				y;
	double			step;
	double			tex_pos;

	range = calculate_draw_range(line_height);
	tex_data.tex_x = calculate_texture_coords(game, &tex_data.texture_index);
	step = 64.0 / line_height;
	tex_pos = (range.start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
	y = range.start;
	while (y <= range.end)
	{
		tex_data.tex_y = (int)tex_pos & 63;
		tex_pos += step;
		put_pixel(x, y,
			get_texture_pixel(&game->textures.tex[tex_data.texture_index],
				tex_data.tex_x, tex_data.tex_y), game);
		y++;
	}
}

void	draw_vertical_line(int x, int line_height, t_game *game)
{
	if (game->textures.loaded)
		draw_vertical_line_texture(x, line_height, game);
	else
		draw_vertical_line_color(x, line_height, game);
}

void	draw_horizontal_line(t_range x_range, int y, int color, t_game *game)
{
	int	x;

	if (y < 0 || y >= SCREEN_HEIGHT)
		return ;
	if (x_range.start < 0)
		x_range.start = 0;
	if (x_range.end >= SCREEN_WIDTH)
		x_range.end = SCREEN_WIDTH - 1;
	x = x_range.start;
	while (x <= x_range.end)
	{
		put_pixel(x, y, color, game);
		x++;
	}
}
