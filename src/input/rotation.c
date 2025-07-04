/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:28:53 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/04 22:47:35 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keypress_rotation(int keycode, t_game *game)
{
	double	old_dir_x;
	double	old_dir_y;
	double	old_plane_x;
	double	angle;

	old_dir_x = game->parsed_data.dir_x;
	old_dir_y = game->parsed_data.dir_y;
	old_plane_x = game->parsed_data.plane_x;
	if (keycode == KEY_LEFT)
		angle = -0.02;
	else if (keycode == KEY_RIGHT)
		angle = 0.02;
	else
		return (0);
	game->parsed_data.dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
	game->parsed_data.dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
	game->parsed_data.plane_x = old_plane_x * cos(angle)
		- game->parsed_data.plane_y * sin(angle);
	game->parsed_data.plane_y = old_plane_x * sin(angle)
		+ game->parsed_data.plane_y * cos(angle);
	return (0);
}
