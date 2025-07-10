/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:35:00 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/10 11:10:29 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Version bonus de update_player qui utilise ray_casting_bonus
int	update_player_bonus(t_game *game)
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
		rotate_player(-0.1, game);
	if (game->keys.r_press)
		rotate_player(0.1, game);
	ray_casting_bonus(game);
	mlx_put_image_to_window(game->mlx_data.mlx, game->mlx_data.win,
		game->mlx_data.img, 0, 0);
	return (0);
}

void	rotate_player(double angle, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->parsed_data.dir_x;
	old_plane_x = game->parsed_data.plane_x;
	game->parsed_data.dir_x = old_dir_x * cos(angle) - game->parsed_data.dir_y
		* sin(angle);
	game->parsed_data.dir_y = old_dir_x * sin(angle) + game->parsed_data.dir_y
		* cos(angle);
	game->parsed_data.plane_x = old_plane_x * cos(angle)
		- game->parsed_data.plane_y * sin(angle);
	game->parsed_data.plane_y = old_plane_x * sin(angle)
		+ game->parsed_data.plane_y * cos(angle);
}

// Fonction pour gérer la rotation avec la souris
int	mouse_rotation(int x, int y, void *param)
{
	t_game	*game;
	int		center_x;
	int		delta_x;
	double	angle;

	(void)y;
	game = (t_game *)param;
	center_x = SCREEN_WIDTH / 2;
	delta_x = x - center_x;
	if (delta_x != 0)
	{
		angle = delta_x * SENSITIVITY;
		rotate_player(angle, game);
		mlx_mouse_move(game->mlx_data.mlx, game->mlx_data.win, center_x,
			SCREEN_HEIGHT / 2);
	}
	return (0);
}

// Fonction main pour la version bonus (à compiler uniquement pour le bonus)
int	main(int ac, char **av)
{
	t_game	game;

	memset(&game, 0, sizeof(t_game));
	init_game(&game, ac, av);
	if (init_mlx(&game.mlx_data) != 0 || init_keys(&game.keys) != 0)
		return (1);
	if (!load_all_textures(&game))
	{
		quity(&game, 1, "erreur textures");
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.mlx_data.mlx);
	manage_mouse_events(&game, 0);
	quity(&game, 0, "finito");
	return (0);
}
