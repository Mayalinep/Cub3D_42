/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:14:24 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/08 13:21:33 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game, int ac, char **av)
{
	set_zero(game);
	verif_part_one(ac, av, game);
	verif_part_two(game);
	if (!game->parsed_data.map[0])
		quity(game, -1, "map vide");
	if (game->parsed_data.p_num != 1)
		quity(game, -1, "nombre de jouers incorrects");
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
		return (-1);
	get_map(game->parsed_data.file, game);
	close(game->parsed_data.file);
	return (0);
}

void	print_all(t_game *game)
{
	// int i = 0;
	printf("les couleurs du ciel r = %i\ng = %i\nb = %i\n", game->parsed_data.ceiling_r,
	game->parsed_data.ceiling_g,
	game->parsed_data.ceiling_b);
	printf("les couleurs du sol r = %i\n g = %i\nb = %i\n", game->parsed_data.floor_r,
	game->parsed_data.floor_g,
	game->parsed_data.floor_b);
	// while (game->parsed_data.map[i])
	// 	printf("le ligne %s", game->parsed_data.map[i++]);
	printf("les textures sud %s\nles textures est %s\nles textures west %s\nles textures nord %s\n",
		game->parsed_data.texture_south, game->parsed_data.texture_east, game->parsed_data.texture_east, game->parsed_data.texture_north);
	
}

void	verif_part_two(t_game *game)
{
	int	i;
	int	j;

	// print_all(game);
	if (!game->parsed_data.texture_south || !game->parsed_data.texture_east
		|| !game->parsed_data.texture_west || !game->parsed_data.texture_north)
		quity(game, 5, "textures inorrectes");
	i = 0;
	j = 0;
	while (game->parsed_data.map[j])
	{
		while (game->parsed_data.map[j][i])
		{
			if (ft_strlen(game->parsed_data.map[j])
				> game->parsed_data.map_width)
				game->parsed_data.map_width
					= ft_strlen(game->parsed_data.map[j]);
			if (player_or_sp(game->parsed_data.map[j][i], game, i, j)
				&& look_side(game->parsed_data.map, i, j, game) == 1)
				quity(game, 2, "map open");
			i++;
		}
		i = 0;
		j++;
	}
	game->parsed_data.map_height = j;
}

void	get_map(int file, t_game *game)
{
	int		i;
	int		flag;
	int		fl;
	char	*line;

	i = 0;
	flag = 1;
	fl = 0;
	while (flag)
	{
		line = get_next_line(file);
		if (!line)
			break ;
		if (*line == '1')
			fl = 1;
		if (*line == '\n' && fl != 1)
			free(line);
		else if (look_one(line, game) != 0)
			flag = add_line(game, line, i++);
		else
			free(line);
	}
	pad_map_lines(game->parsed_data.map);
	// for (int k = 0; game->parsed_data.map[k]; k++)
	// 	printf("map[%d] = \"%s\"\n", k, game->parsed_data.map[k]);
	//end_map(game->parsed_data.map, i);
}
