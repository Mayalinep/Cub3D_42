#ifndef DRAW_H
#define DRAW_H

#include "cub3d.h"

typedef struct s_x_range
{
	int	start_x;
	int	end_x;
}	t_x_range;

typedef struct s_y_range
{
	int	start_y;
	int	end_y;
}	t_y_range;

void		put_pixel(int x, int y, int color, t_game *game);
int			get_wall_color(t_raycasting *ray);
int			get_texture_index(t_raycasting *ray);
int			calculate_texture_coords(t_game *game, int *texture_index);
t_y_range	calculate_draw_range(int line_height);
void		draw_vertical_line_color(int x, int line_height, t_game *game);
void		draw_vertical_line_texture(int x, int line_height, t_game *game);
void		draw_vertical_line(int x, int line_height, t_game *game);
void		draw_horizontal_line(t_x_range x_range, int y, int color, t_game *game);
int			create_rgb_color(int r, int g, int b);
void		draw_floor_and_ceiling(t_game *game);
void		draw_minimap(t_game *game);
void		draw_minimap_walls(t_game *game);
void		draw_minimap_player(t_game *game);
void		draw_minimap_square(int map_x, int map_y, int scale, int offset_x, 
		int offset_y, int color, t_game *game);

#endif
