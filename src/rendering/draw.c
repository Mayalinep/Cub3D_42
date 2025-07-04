/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:53:34 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/04 22:43:32 by ssoukoun         ###   ########.fr       */
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

void	draw_vertical_line_texture(int x, int line_height, t_game *game)
{
	int		draw_start;
	int		draw_end;
	int		texture_index;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		y;

	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	step = 64.0 / line_height;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
	texture_index = get_texture_index(&game->raycasting);
	tex_x = (int)(game->raycasting.wall_x * 64);
	if (game->raycasting.side == 0 && game->raycasting.step_x < 0)
		tex_x = 64 - tex_x - 1;
	if (game->raycasting.side == 1 && game->raycasting.step_y > 0)
		tex_x = 64 - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x > 63)
		tex_x = 63;
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos & 63;
		tex_pos += step;
		put_pixel(x, y, get_texture_pixel(&game->textures.tex[texture_index],
				tex_x, tex_y), game);
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

void	draw_horizontal_line(int start_x, int end_x, int y, int color,
		t_game *game)
{
	int	x;

	if (y < 0 || y >= SCREEN_HEIGHT)
		return ;
	if (start_x < 0)
		start_x = 0;
	if (end_x >= SCREEN_WIDTH)
		end_x = SCREEN_WIDTH - 1;
	x = start_x;
	while (x <= end_x)
	{
		put_pixel(x, y, color, game);
		x++;
	}
}

int	create_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

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
			draw_horizontal_line(0, SCREEN_WIDTH - 1, y, ceiling_color, game);
		else
			draw_horizontal_line(0, SCREEN_WIDTH - 1, y, floor_color, game);
		y++;
	}
}
