/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:22:30 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/30 12:54:44 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

// Fonction de nettoyage
void	cleanup_game(t_game *game)
{
	cleanup_textures(game);
	if (game->mlx_data.img)
		mlx_destroy_image(game->mlx_data.mlx, game->mlx_data.img);
	if (game->mlx_data.win)
		mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
	if (game->mlx_data.mlx)
		mlx_destroy_display(game->mlx_data.mlx);
}

// Initialisation des textures
void	init_textures(t_textures *textures)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		textures->tex[i].img = NULL;
		textures->tex[i].addr = NULL;
		textures->tex[i].bpp = 0;
		textures->tex[i].line_len = 0;
		textures->tex[i].endian = 0;
		i++;
	}
	textures->loaded = 0;
}

// Fonction principale
int	main(void)
{
	t_game game;
	
	// Initialisation à zéro pour éviter les valeurs aléatoires
	memset(&game, 0, sizeof(t_game));
	
	// Initialisation des textures
	init_textures(&game.textures);
	
	printf("Début du programme\n");
	
	int parsing_result = simulate_parsing(&game.parsed_data);
	printf("Résultat du parsing: %d\n", parsing_result);
	
	if (parsing_result != 0)
	{
		printf("Erreur lors du parsing\n");
		return (1);
	}
	
	printf("Parsing réussi, initialisation MLX...\n");
	
	if (init_mlx(&game.mlx_data) != 0 || init_keys(&game.keys) != 0)
	{
		printf("Erreur lors de l'initialisation de la minilibx\n");
		return (1);
	}
	
	printf("MLX initialisé avec succès\n");
	
	// Chargement des textures
	printf("Chargement des textures...\n");
	if (!load_all_textures(&game))
	{
		printf("Erreur lors du chargement des textures\n");
		cleanup_game(&game);
		return (1);
	}
	
	mlx_hook(game.mlx_data.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.mlx_data.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_hook(game.mlx_data.win, 17, 1L << 17, handle_close, &game);
	mlx_loop_hook(game.mlx_data.mlx, update_player, &game);
	mlx_loop(game.mlx_data.mlx);
	
	cleanup_game(&game);
	return (0);
}
