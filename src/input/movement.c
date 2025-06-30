/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:27:42 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/30 14:20:15 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>
#include <math.h>

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

// Vérification des coins pour éviter de passer à travers
int	check_corner_collision(double new_x, double new_y, t_parsed_data *data)
{
	int	old_x;
	int	old_y;
	int	new_map_x;
	int	new_map_y;

	old_x = (int)data->player_x;
	old_y = (int)data->player_y;
	new_map_x = (int)new_x;
	new_map_y = (int)new_y;
	
	// Si on change de case ET qu'on se déplace en diagonale
	if ((new_map_x != old_x || new_map_y != old_y) && 
		(new_map_x != old_x && new_map_y != old_y))
	{
		// Vérifier les coins
		if (new_map_x > old_x && new_map_y < old_y)
		{
			if (new_map_x - 1 >= 0 && data->map[new_map_y][new_map_x - 1] == '1' &&
				new_map_y + 1 < data->map_height && data->map[new_map_y + 1][new_map_x] == '1')
				return (1);
		}
		else if (new_map_x > old_x && new_map_y > old_y)
		{
			if (new_map_x - 1 >= 0 && data->map[new_map_y][new_map_x - 1] == '1' &&
				new_map_y - 1 >= 0 && data->map[new_map_y - 1][new_map_x] == '1')
				return (1);
		}
		else if (new_map_x < old_x && new_map_y < old_y)
		{
			if (new_map_x + 1 < data->map_width && data->map[new_map_y][new_map_x + 1] == '1' &&
				new_map_y + 1 < data->map_height && data->map[new_map_y + 1][new_map_x] == '1')
				return (1);
		}
		else if (new_map_x < old_x && new_map_y > old_y)
		{
			if (new_map_x + 1 < data->map_width && data->map[new_map_y][new_map_x + 1] == '1' &&
				new_map_y - 1 >= 0 && data->map[new_map_y - 1][new_map_x] == '1')
				return (1);
		}
	}
	return (0);
}

// Vérifie si une position est trop proche d'un mur
int	is_too_close_to_wall(double x, double y, t_parsed_data *data, double margin)
{
	int		check_x;
	int		check_y;
	int		map_x;
	int		map_y;
	
	// Vérifier un carré autour du joueur
	check_y = -1;
	while (check_y <= 1)
	{
		check_x = -1;
		while (check_x <= 1)
		{
			// Position à vérifier
			map_x = (int)(x + check_x * margin);
			map_y = (int)(y + check_y * margin);
			
			// Vérifier les limites
			if (map_x < 0 || map_x >= data->map_width || 
				map_y < 0 || map_y >= data->map_height)
				return (1);
			
			// Si c'est un mur, on est trop proche
			if (data->map[map_y][map_x] == '1')
				return (1);
			
			check_x++;
		}
		check_y++;
	}
	return (0);
}

int	wall_collision(double new_x, double new_y, t_parsed_data *data)
{
	double	margin;
	
	margin = 0.2; // Distance minimale aux murs (réduite de 0.3 à 0.2)
	
	// Vérification des limites de la map avec marge
	if (new_y < margin || new_y >= data->map_height - margin || 
		new_x < margin || new_x >= data->map_width - margin)
		return (1);
	
	// Vérification de collision avec un mur
	if (data->map[(int)new_y][(int)new_x] == '1')
		return (1);
	
	// Vérifier si on est trop proche d'un mur
	if (is_too_close_to_wall(new_x, new_y, data, margin))
		return (1);
	
	return (0);
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
	mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win, game->mlx_data.img, 0, 0);
	return (0);
}
