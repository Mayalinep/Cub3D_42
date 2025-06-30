/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:22:30 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/30 15:15:03 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Fonction principale
int	main(int ac, char **av)
{
	t_game game;
	
	// Initialisation à zéro pour éviter les valeurs aléatoires
	memset(&game, 0, sizeof(t_game));
	
	printf("Début du programme\n");
	init_game(&game, ac, av);
	printf("Parsing réussi, initialisation MLX...\n");
	
	if (init_mlx(&game.mlx_data) != 0 || init_keys(&game.keys) != 0)
	{
		printf("Erreur lors de l'initialisation de la minilibx\n");
		return (1);
	}
	printf("MLX initialisé avec succès\n");
	
	if (!load_all_textures(&game))
	{
		printf("Erreur lors du chargement des textures\n");
		quity(&game, 1, "erreur textures");
		return (1);
	}
	
	printf("Lancement de la boucle de jeu...\n");
	mlx_hook(game.mlx_data.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.mlx_data.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_hook(game.mlx_data.win, 17, 1L << 17, handle_close, &game);
	mlx_loop_hook(game.mlx_data.mlx, update_player, &game);
	mlx_loop(game.mlx_data.mlx);
	quity(&game, 0, "finito");
	return (0);
}
