/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:26:02 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/30 15:01:05 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->parsed_data.map)
	{
		while (i < MAX_MAP_LINES && game->parsed_data.map[i])
		{
			if (game->parsed_data.map[i])
				free(game->parsed_data.map[i]);
			i++;
		}
		free(game->parsed_data.map);
	}
}

void	free_textures(t_game *game)
{
	int i;
	
	// Libération des chemins de textures
	if (game->parsed_data.texture_south)
		free(game->parsed_data.texture_south);
	if (game->parsed_data.texture_east)
		free(game->parsed_data.texture_east);
	if (game->parsed_data.texture_west)
		free(game->parsed_data.texture_west);
	if (game->parsed_data.texture_north)
		free(game->parsed_data.texture_north);
	
	// Libération des images MLX (adapté à ta structure tex[4])
	if (game->mlx_data.mlx)
	{
		i = 0;
		while (i < 4)
		{
			if (game->textures.tex[i].img)
				mlx_destroy_image(game->mlx_data.mlx, game->textures.tex[i].img);
			i++;
		}
	}
}

void	free_mlx(t_game *game)
{
	if (game->mlx_data.img && game->mlx_data.mlx)
		mlx_destroy_image(game->mlx_data.mlx, game->mlx_data.img);
	if (game->mlx_data.win)
		mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
	if (game->mlx_data.mlx)
	{
		mlx_destroy_display(game->mlx_data.mlx);
		free(game->mlx_data.mlx);
	}
}

void	quity(t_game *game, int j, char *str)
{
	free_map(game);
	free_textures(game);
	free_mlx(game);
	printf("exit :%s\n", str);
	exit(j);
}
