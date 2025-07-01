/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:27:42 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/01 17:42:28 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <time.h>

// Calcul de la vitesse adaptative basée sur le temps
double	calculate_adaptive_speed(void)
{
	static clock_t	prev_time = 0;
	double			diff;
	double			speed;

	if (prev_time == 0)
		prev_time = clock();
	diff = (double)(clock() - prev_time) / CLOCKS_PER_SEC;
	prev_time = clock();
	// Vitesse de base adaptée au temps écoulé
	speed = diff * 5.0;
	if (speed > 0.1)
		speed = 0.1;
	if (speed < 0.01)
		speed = 0.01;
	return (speed);
}

int	try_move(t_game *game, double dir_x, double dir_y)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = calculate_adaptive_speed();
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

int	update_player(t_game *game)
{
	if (game->keys.w_press)
		try_move(game, game->parsed_data.dir_x, game->parsed_data.dir_y);
	if (game->keys.s_press)
		try_move(game, -game->parsed_data.dir_x, -game->parsed_data.dir_y);
	if (game->keys.a_press)
		try_move(game, -game->parsed_data.plane_x, -game->parsed_data.plane_y);
	if (game->keys.d_press)
		try_move(game, game->parsed_data.plane_x, game->parsed_data.plane_y);
	if (game->keys.l_press)
		keypress_rotation(KEY_LEFT, game);
	if (game->keys.r_press)
		keypress_rotation(KEY_RIGHT, game);
	ray_casting(game);
	mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
		game->mlx_data.img, 0, 0);
	return (0);
}
