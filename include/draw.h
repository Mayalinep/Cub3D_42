#ifndef DRAW_H
#define DRAW_H

#include "cub3d.h"

void draw_vertical_line_color(int x, int line_height, t_game *game);
void draw_vertical_line_texture(int x, int line_height, t_game *game);
void draw_vertical_line(int x, int line_height, t_game *game);
void put_pixel(int x, int y, int color, t_game *game);

#endif
