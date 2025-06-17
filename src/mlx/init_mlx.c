/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:22:24 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/17 12:22:27 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Fonction pour initialiser la minilibx
int	init_mlx(t_mlx_data *mlx_data)
{
	mlx_data->mlx = mlx_init(); // Initialisation de la minilibx
	if (mlx_data->mlx == NULL)
	{
		printf("Erreur lors de l'initialisation de la minilibx\n");
		return (1);
	}
	mlx_data->win = mlx_new_window(mlx_data->mlx, 1000, 1000, "Cub3D");
	if (mlx_data->win == NULL)
	{
		printf("Erreur lors de la creation de la fenetre\n");
		return (1);
	}
	mlx_data->img = mlx_new_image(mlx_data->mlx, 1000, 1000);
	if (mlx_data->img == NULL)
	{
		printf("Erreur lors de la creation de l'image\n");
		return (1);
	}
	return (0);
}