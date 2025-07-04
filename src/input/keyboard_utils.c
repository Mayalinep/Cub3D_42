/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:17:46 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/01 17:39:07 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_keys(t_keys *keys)
{
	keys->w_press = 0;
	keys->a_press = 0;
	keys->s_press = 0;
	keys->d_press = 0;
	keys->l_press = 0;
	keys->r_press = 0;
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	if (keycode == KEY_W)
		game->keys.w_press = 1;
	if (keycode == KEY_A)
		game->keys.a_press = 1;
	if (keycode == KEY_S)
		game->keys.s_press = 1;
	if (keycode == KEY_D)
		game->keys.d_press = 1;
	if (keycode == KEY_LEFT)
		game->keys.l_press = 1;
	if (keycode == KEY_RIGHT)
		game->keys.r_press = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w_press = 0;
	if (keycode == KEY_A)
		game->keys.a_press = 0;
	if (keycode == KEY_S)
		game->keys.s_press = 0;
	if (keycode == KEY_D)
		game->keys.d_press = 0;
	if (keycode == KEY_LEFT)
		game->keys.l_press = 0;
	if (keycode == KEY_RIGHT)
		game->keys.r_press = 0;
	return (0);
}

int	handle_close(t_game *game)
{
	cleanup_game(game);
	exit(0);
}
