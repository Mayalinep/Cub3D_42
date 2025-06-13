/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:24:03 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/13 17:51:39 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int main(int ac, char **av)
{
    t_game *game;

    game = malloc(sizeof(t_game));
    if (!game)
        return (-1);
    init_game(game);
    verif(ac, av, game);
    print_map(game->map);

    quity(game, 0); // Ajoute cette ligne pour libérer toute la mémoire

    return (0);
}

