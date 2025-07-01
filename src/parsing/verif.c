/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:14:24 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/30 16:27:42 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	verif_part_one(int ac, char **av, t_game *game)
{
	int	i;

	i = ft_strlen(av[1]);
	if (ac != 2)
		return (-1);
	if ((av[1][--i]) != 'b')
		return (-1);
	if ((av[1][--i]) != 'u')
		return (-1);
	if ((av[1][--i]) != 'c')
		return (-1);
	if ((av[1][--i]) != '.')
		return (-1);
	game->parsed_data.file = open(av[1], R_OK);
	if (game->parsed_data.file == -1)
		return (printf("er01\n"), -1);
	get_map(game->parsed_data.file, game);
	// get_next_line(-1);
	return (0);
}

void	set_pos(int i, int j, t_game *game)
{
	char c;

	c = game->parsed_data.map[j][i];
	game->parsed_data.player_x = i;
	game->parsed_data.player_y = j;
	 if (c == 'N') { game->parsed_data.dir_x = 0; game->parsed_data.dir_y = -1; game->parsed_data.plane_x = 0.66; game->parsed_data.plane_y = 0; }
               
	 else if (c == 'S') { game->parsed_data.dir_x = 0; game->parsed_data.dir_y = 1; game->parsed_data.plane_x = -0.66; game->parsed_data.plane_y = 0; }
                
	 else if (c == 'E') { game->parsed_data.dir_x = 1; game->parsed_data.dir_y = 0; game->parsed_data.plane_x = 0; game->parsed_data.plane_y = 0.66; }
                
	 else if (c == 'W') { game->parsed_data.dir_x = -1; game->parsed_data.dir_y = 0; game->parsed_data.plane_x = 0; game->parsed_data.plane_y = -0.66; }
	
}

int	player_or_sp(char c, t_game *game, int i, int j)

{	
	if (c == 'S' || c == 'E' || c == 'N' || c == 'W')
	{
		game->parsed_data.p_num++;
		set_pos(i, j, game);
		return (1);
	}
	if (c == '0')
		return (1);
	return (0);
}

void	verif_part_two(t_game *game)
{
	int	i;
	int	j;

	if (!game->parsed_data.texture_south || !game->parsed_data.texture_east
		|| !game->parsed_data.texture_west
		|| !game->parsed_data.texture_north)
		quity(game, 5, "textures inorrectes");
	i = 0;
	j = 0;
	while (game->parsed_data.map[j])
	{
		while (game->parsed_data.map[j][i]) 
		{
			if(ft_strlen(game->parsed_data.map[j]) > game->parsed_data.map_width)
			 game->parsed_data.map_width = ft_strlen(game->parsed_data.map[j]);
			if (player_or_sp (game->parsed_data.map[j][i], game, i, j)
				&& look_side(game->parsed_data.map, i, j, game) == 1)
				quity(game, 2, "map open");
			i++;
		}
		i = 0;
		j++;
	}
	game->parsed_data.map_height = j;
}
void	set_zero(t_game *game)
{
	int	i;

	i = 0;
	game->parsed_data.p_num = 0;
	game->parsed_data.map_width = 0;
	game->parsed_data.map_height = 0;
	game->parsed_data.ceiling_r = -1;
	game->parsed_data.ceiling_g = -1;
	game->parsed_data.ceiling_b = -1;
	game->parsed_data.floor_r = -1;
	game->parsed_data.floor_g = -1;
	game->parsed_data.floor_b = -1;
	game->parsed_data.texture_south = NULL;
	game->parsed_data.texture_north = NULL;
	game->parsed_data.texture_west = NULL;
	game->parsed_data.texture_east = NULL;
	game->parsed_data.map = malloc(sizeof(char *) * MAX_MAP_LINES);
	if (!game->parsed_data.map)
		exit(-2);
	while (i < MAX_MAP_LINES)
		game->parsed_data.map[i++] = NULL;
}

void	init_game(t_game *game, int ac, char **av)
{
	set_zero(game);
	verif_part_one(ac, av, game);
	verif_part_two(game);
	if (game->parsed_data.p_num != 1)
		quity(game, -1, "nombre de jouers incorrects\n");
	//print_all(game);
}

void	print_all(t_game *game)
{
	int i = 0;
	printf("les couleurs du ciel r = %i\n g = %i\nb = %i\n", game->parsed_data.ceiling_r,
	game->parsed_data.ceiling_g,
	game->parsed_data.ceiling_b);
	printf("les couleurs du sol r = %i\n g = %i\nb = %i\n", game->parsed_data.floor_r,
	game->parsed_data.floor_g,
	game->parsed_data.floor_b);
	while (game->parsed_data.map[i])
		printf("le ligne %s", game->parsed_data.map[i++]);
	printf("les textures sud %sles textures est %sles textures west %sles textures nord %s",
		game->parsed_data.texture_south, game->parsed_data.texture_east, game->parsed_data.texture_east, game->parsed_data.texture_north);
	
}