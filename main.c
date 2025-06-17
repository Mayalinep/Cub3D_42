/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:22:30 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/17 16:44:33 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Fonction principale
int	main(void)
{
	t_game game;
	if (simulate_parsing(&game.parsed_data) != 0)
	{
		printf("Erreur lors du parsing\n");
		return (1);
	}
	if (init_mlx(&game.mlx_data) != 0 || init_keys(&game.keys) != 0)
	{
		printf("Erreur lors de l'initialisation de la minilibx\n");
		return (1);
	}
	mlx_hook(game.mlx_data.win, 2, 1L << 0, handle_keypress, &game); // 2 = evenement de touche, 1L << 0 = touche pressee,handle_keypress = fonction a appeler lors de l evenement,&data = donnees a passer a la fonction
	mlx_hook(game.mlx_data.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_hook(game.mlx_data.win, 17, 1L << 17, handle_close, &game); // 17 = evenement de fermeture de la fenetre, 1L << 17 = fermeture de la fenetre handle_close = fonction a appeler lors de l evenement, &data = donnees a passer a la fonction
	mlx_loop_hook(game.mlx_data.mlx, update_player, &game);
	mlx_loop(game.mlx_data.mlx);
	return (0);
}
