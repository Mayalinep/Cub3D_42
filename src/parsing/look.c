/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:27:15 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/04 22:29:09 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		|| game->parsed_data.ceiling_r < 0 || game->parsed_data.ceiling_r > 255
		|| game->parsed_data.ceiling_g < 0 || game->parsed_data.ceiling_g > 255)
		return (-1);
	if (game->parsed_data.floor_b < 0 || game->parsed_data.floor_b > 255
		|| game->parsed_data.floor_g < 0 || game->parsed_data.floor_g > 255
		|| game->parsed_data.floor_r < 0 || game->parsed_data.floor_r > 255)
		return (-1);
	return (0);
}
