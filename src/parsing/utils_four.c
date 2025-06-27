/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:26:02 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/27 19:05:25 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"

void	quity(t_game *game, int j, char *str)
{
	free_map(game);
	free_textures(game);
	free_mlx(game);
	printf("exit :%s\n", str);
	exit(j);
}

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
	if (game->parsed_data.texture_south)
		free(game->parsed_data.texture_south);
	if (game->parsed_data.texture_east)
		free(game->parsed_data.texture_east);
	if (game->parsed_data.texture_west)
		free(game->parsed_data.texture_west);
	if (game->parsed_data.texture_north)
		free(game->parsed_data.texture_north);
	if (game->mlx_data.mlx)
	{
		if (game->textures.north_img)
			mlx_destroy_image(game->mlx_data.mlx, game->textures.north_img);
		if (game->textures.south_img)
			mlx_destroy_image(game->mlx_data.mlx, game->textures.south_img);
		if (game->textures.east_img)
			mlx_destroy_image(game->mlx_data.mlx, game->textures.east_img);
		if (game->textures.west_img)
			mlx_destroy_image(game->mlx_data.mlx, game->textures.west_img);
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
