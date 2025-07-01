/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:27:15 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/27 15:20:41 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// regarde si y a des '0' dehors
int	look_side(char **map, int i, int j, t_game *game)
{
	if (!map || !map[j] || i < 1 || j < 1)
		return (-1);
	if (!map[j + 1] || !map[j - 1])
		quity(game, 2, "map invalide");
	if ((int)ft_strlen(map[j - 1]) <= i || (int)ft_strlen(map[j + 1]) <= i)
		quity(game, 2, "map invalide");
	if ((int)ft_strlen(map[j]) <= i + 1 || i <= 0)
		quity(game, 2, "map invalide");
	if (map[j + 1][i] != '0' && map[j + 1][i] != '1' && map[j + 1][i] != 'N')
		quity(game, 2, "map invalide");
	if (map[j - 1][i] != '0' && map[j - 1][i] != '1' && map[j - 1][i] != 'N')
		quity(game, 2, "map invalide");
	if ((int)ft_strlen(map[j]) <= i + 1)
		quity(game, 2, "map invalide");
	if (map[j][i + 1] != '0' && map[j][i + 1] != '1' && map[j][i + 1] != 'N')
		quity(game, 2, "map invalide");
	if (i >= (int)ft_strlen(map[j]) || i <= 0)
		quity(game, 2, "map invalide");
	if (map[j][i - 1] != '0' && map[j][i - 1] != '1' && map[j][i - 1] != 'N')
		quity(game, 2, "map invalide");
	return (0);
}

// regarde si les sprites existent et les limites des couleurs
int	look_sprites(t_game *game)
{
	if (!game->parsed_data.texture_south)
		return (-1);
	if (!game->parsed_data.texture_east)
		return (-1);
	if (!game->parsed_data.texture_west)
		return (-1);
	if (!game->parsed_data.texture_north)
		return (-1);
	if (game->parsed_data.ceiling_b < 0 || game->parsed_data.ceiling_b > 255
		|| game->parsed_data.ceiling_r < 0
		|| game->parsed_data.ceiling_r > 255
		|| game->parsed_data.ceiling_g < 0
		|| game->parsed_data.ceiling_g > 255)
		return (-1);
	if (game->parsed_data.floor_b < 0 || game->parsed_data.floor_b > 255
		|| game->parsed_data.floor_g < 0 || game->parsed_data.floor_g > 255
		|| game->parsed_data.floor_r < 0 || game->parsed_data.floor_r > 255)
		return (-1);
	return (0);
}
