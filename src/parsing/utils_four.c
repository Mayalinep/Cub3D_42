/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:26:02 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/27 16:04:33 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	quity(t_game *game, int j, char *str)
{
	int	i;

	i = 0;
	if (game->parsed_data.map)
	{
		while (i < MAX_MAP_LINES)
		{
			if (game->parsed_data.map[i])
				free(game->parsed_data.map[i]);
			i++;
		}
		free(game->parsed_data.map);
	}
	if (game->parsed_data.texture_south)
		free(game->parsed_data.texture_south);
	if (game->parsed_data.texture_east)
		free(game->parsed_data.texture_east);
	if (game->parsed_data.texture_west)
		free(game->parsed_data.texture_west);
	if (game->parsed_data.texture_north)
		free(game->parsed_data.texture_north);
	if (game->mlx_data.img)
		mlx_destroy_image(game->mlx_data.mlx, game->mlx_data.img);
	if (game->mlx_data.win)
		mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
	if (game->mlx_data.mlx)
	{
		mlx_destroy_display(game->mlx_data.mlx);
		free(game->mlx_data.mlx);
	}
	printf("exit :%s\n", str);
	exit(j);
}
