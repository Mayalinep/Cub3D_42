/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:17:46 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/27 15:50:06 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_keys(t_keys *keys)
{
    keys->w_press = 0;
    keys->a_press = 0;
    keys->s_press = 0;
    keys->d_press = 0;
    keys->l_press = 0;
    keys->r_press = 0;
    return (0);
}

int handle_keypress(int keycode, t_game *game)
{
    if(keycode == KEY_ESC)
    {
        quity(game, 0, "echap\n\n\n");
        mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
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
int handle_keyrelease(int keycode, t_game *game)
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
    quity(game, 0, "cross press\n");
	mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
	exit(0);
}
