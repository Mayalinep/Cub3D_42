/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:59:05 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/26 17:35:26 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_part_two(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->parsed_data.map[i])
	{
		if (ft_strlen(game->parsed_data.map[i]) > j)
			j = ft_strlen(game->parsed_data.map[i]);
		i++;
	}
	game->parsed_data.map_height = j;
	game->parsed_data.map_width = i;
}
