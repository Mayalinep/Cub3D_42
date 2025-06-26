#ifndef DRAW_H
#define DRAW_H

#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game);
int		get_wall_color(t_raycasting *ray);
void	draw_vertical_line_color(int x, int line_height, t_game *game);
void	draw_vertical_line_texture(int x, int line_height, t_game *game);
void	draw_vertical_line(int x, int line_height, t_game *game);
int		create_rgb_color(int r, int g, int b);
void	draw_floor_and_ceiling(t_game *game);
void	draw_minimap(t_game *game);
void	draw_minimap_walls(t_game *game);
void	draw_minimap_player(t_game *game);
void	draw_minimap_square(int map_x, int map_y, int scale, int offset_x, 
		int offset_y, int color, t_game *game);

#endif
