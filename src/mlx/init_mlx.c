/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:22:24 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/10 14:41:19 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx_core(t_mlx_data *mlx_data)
{
	mlx_data->mlx = mlx_init();
	if (mlx_data->mlx == NULL)
	{
		printf("Erreur: initialisation de la minilibx\n");
		return (1);
	}
	mlx_data->win = mlx_new_window(mlx_data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Cub3D");
	if (mlx_data->win == NULL)
	{
		printf("Erreur: creation de la fenetre\n");
		return (1);
	}
	return (0);
}

int	init_mlx_image(t_mlx_data *mlx_data)
{
	mlx_data->img = mlx_new_image(mlx_data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (mlx_data->img == NULL)
	{
		printf("Erreur:creation de l'image\n");
		return (1);
	}
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, &mlx_data->bits_per_pixel,
			&mlx_data->line_length, &mlx_data->endian);
	if (mlx_data->addr == NULL)
	{
		return (printf("Erreur:recuperation de l'adresse de l'image\n"), 1);
	}
	return (0);
}

int	init_mlx(t_mlx_data *mlx_data)
{
	if (init_mlx_core(mlx_data) != 0)
		return (1);
	if (init_mlx_image(mlx_data) != 0)
		return (1);
	return (0);
}
