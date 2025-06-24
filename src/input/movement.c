/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:27:42 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/24 09:09:57 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	wall_collision(double new_x, double new_y, t_parsed_data *data)
{
	// Vérification des limites de la map
	if ((int)new_y < 0 || (int)new_y >= data->map_height || (int)new_x < 0
		|| (int)new_x >= data->map_width)
		return (1);
	// Vérification de collision avec un mur
	if (data->map[(int)new_y][(int)new_x] == '1')
		return (1);
	return (0);
}

int	try_move(t_game *game, double dir_x, double dir_y)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = 0.1;
	new_x = game->parsed_data.player_x + dir_x * speed;
	new_y = game->parsed_data.player_y + dir_y * speed;
	if (!wall_collision(new_x, new_y, &game->parsed_data))
	{
		game->parsed_data.player_x = new_x;
		game->parsed_data.player_y = new_y;
		return (1);
	}
	return (0);
}
int update_player(t_game *game)
{
    if(game->keys.w_press)
        try_move(game, game->parsed_data.dir_x, game->parsed_data.dir_y);
    if(game->keys.s_press)
        try_move(game, -game->parsed_data.dir_x, -game->parsed_data.dir_y);
    if(game->keys.a_press)
        try_move(game, -game->parsed_data.plane_x, -game->parsed_data.plane_y);
    if(game->keys.d_press)
        try_move(game, game->parsed_data.plane_x, game->parsed_data.plane_y);
    if(game->keys.l_press)
        keypress_rotation(KEY_LEFT, game);
    if(game->keys.r_press)
        keypress_rotation(KEY_RIGHT, game);
    return (0);
}
