/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:08:07 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/10 14:58:36 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_minimap_coords	calculate_minimap_coords(int map_x, int map_y, t_game *game)
{
	t_minimap_coords	coords;

	coords.scale = 8;
	coords.offset_x = SCREEN_WIDTH - (game->parsed_data.map_width
			* coords.scale) - 20;
	coords.offset_y = 20;
	coords.screen_x = map_x * coords.scale + coords.offset_x;
	coords.screen_y = map_y * coords.scale + coords.offset_y;
	return (coords);
}

// Fonction pour gérer les événements souris (init ou cleanup)
void	manage_mouse_events(t_game *game, int init)
{
	if (init)
	{
		mlx_mouse_move(game->mlx_data.mlx, game->mlx_data.win, SCREEN_WIDTH / 2,
			SCREEN_HEIGHT / 2);
		mlx_hook(game->mlx_data.win, 6, 1L << 6, mouse_rotation, game);
	}
	else
	{
		if (game->mlx_data.mlx && game->mlx_data.win)
			mlx_mouse_show(game->mlx_data.mlx, game->mlx_data.win);
	}
}

// Fonction pour configurer tous les hooks du jeu
void	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx_data.win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->mlx_data.win, 3, 1L << 1, handle_keyrelease, game);
	manage_mouse_events(game, 1);
	mlx_hook(game->mlx_data.win, 17, 1L << 17, handle_close, game);
	mlx_loop_hook(game->mlx_data.mlx, update_player_bonus, game);
}
