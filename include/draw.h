/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:11:00 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/10 15:33:47 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "cub3d.h"

typedef struct s_range
{
	int				start;
	int				end;
}					t_range;

typedef struct s_texture_data
{
	int				tex_x;
	int				tex_y;
	int				texture_index;
}					t_texture_data;

typedef struct s_minimap_coords
{
	int				screen_x;
	int				screen_y;
	int				scale;
	int				offset_x;
	int				offset_y;
}					t_minimap_coords;

void				put_pixel(int x, int y, int color, t_game *game);
int					get_wall_color(t_raycasting *ray);
int					get_texture_index(t_raycasting *ray);
int					calculate_texture_coords(t_game *game, int *texture_index);
t_range				calculate_draw_range(int line_height);
void				draw_vertical_line_color(int x, int line_height,
						t_game *game);
void				draw_vertical_line_texture(int x, int line_height,
						t_game *game);
void				draw_vertical_line(int x, int line_height, t_game *game);
void				draw_horizontal_line(t_range x_range, int y, int color,
						t_game *game);
int					create_rgb_color(int r, int g, int b);
void				draw_floor_and_ceiling(t_game *game);
t_minimap_coords	calculate_minimap_coords(int map_x, int map_y,
						t_game *game);
void				draw_minimap(t_game *game);
void				draw_minimap_walls(t_game *game);
void				draw_minimap_player(t_game *game);
void				draw_minimap_direction(t_game *game);

#endif
