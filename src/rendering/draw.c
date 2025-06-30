/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:53:34 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/30 16:27:42 by mpelage          ###   ########.fr       */
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
	// Optimisation : utiliser les bits pour déterminer la couleur
	// side = 0 (vertical) ou 1 (horizontal)
	// step_x/step_y = -1 ou 1
	int	color_index;

	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			color_index = 1;  // EAST
		else
			color_index = 0;  // WEST
	}
	else
	{
		if (ray->step_y > 0)
			color_index = 3;  // SOUTH
		else
			color_index = 2;  // NORTH
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

// Fonction pour déterminer quelle texture utiliser
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

	// Calcul des positions de dessin
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	
	// Calcul du step pour la texture
	step = 64.0 / line_height;
	
	// Limiter draw_start AVANT de calculer tex_pos (comme le code d'inspiration)
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	
	// Maintenant calculer tex_pos avec draw_start déjà limité
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
		put_pixel(x, y, get_texture_pixel(&game->textures.tex[texture_index], tex_x, tex_y), game);
		y++;
	}
}

void	draw_vertical_line(int x, int line_height, t_game *game)
{
	// Système de fallback : textures si chargées, sinon couleurs
	if (game->textures.loaded)
		draw_vertical_line_texture(x, line_height, game);
	else
		draw_vertical_line_color(x, line_height, game);
}

// Fonction pour dessiner une ligne horizontale
void	draw_horizontal_line(int start_x, int end_x, int y, int color, t_game *game)
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

// Fonction pour créer une couleur RGB
int	create_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

// Fonction optimisée pour dessiner le sol et le ciel
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

// Fonction pour dessiner la mini-map
void	draw_minimap(t_game *game)
{
	draw_minimap_walls(game);
	draw_minimap_player(game);
}

// Fonction pour dessiner les murs de la mini-map
void	draw_minimap_walls(t_game *game)
{
	int	x;
	int	y;
	int	scale;
	int	offset_x;
	int	offset_y;
	int	line_len;

	scale = 8;
	offset_x = SCREEN_WIDTH - (game->parsed_data.map_width * scale) - 20;
	offset_y = 20;
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
				{
					draw_minimap_square(x, y, scale, offset_x, offset_y, 
						0x404040, game);
				}
				else
				{
					draw_minimap_square(x, y, scale, offset_x, offset_y, 
						0x202020, game);
				}
				x++;
			}
		}
		y++;
	}
}

// Fonction pour dessiner un carré dans la mini-map
void	draw_minimap_square(int map_x, int map_y, int scale, int offset_x, 
		int offset_y, int color, t_game *game)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;

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

// Fonction pour dessiner le joueur sur la mini-map
void	draw_minimap_player(t_game *game)
{
	int	scale;
	int	offset_x;
	int	offset_y;
	int	player_x;
	int	player_y;
	int	x;
	int	y;

	scale = 8;
	offset_x = SCREEN_WIDTH - (game->parsed_data.map_width * scale) - 20;
	offset_y = 20;
	player_x = (int)(game->parsed_data.player_x * scale) + offset_x;
	player_y = (int)(game->parsed_data.player_y * scale) + offset_y;
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

