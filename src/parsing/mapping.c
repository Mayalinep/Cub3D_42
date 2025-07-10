/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:31:38 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/10 15:28:35 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	look_one_two(char *line, t_game *game)
{
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "F", 1) == 0)
		return (set_floor_cell(line, game, "F ", 0), 0);
	if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "C", 2) == 0)
		return (set_floor_cell(line, game, "C ", 0), 0);
	free(line);
	return (1);
}

int	look_one(char *line, t_game *game)
{
	char	*tr;

	tr = k_spaces(line);
	if (ft_strncmp(tr, "SO ", 3) == 0 && !game->parsed_data.texture_south)
	{
		game->parsed_data.texture_south = ft_dup_ws(tr, 2);
		return (0);
	}
	if (ft_strncmp(tr, "NO ", 3) == 0 && !game->parsed_data.texture_north)
	{
		game->parsed_data.texture_north = ft_dup_ws(tr, 2);
		return (0);
	}
	if (ft_strncmp(tr, "WE ", 3) == 0 && !game->parsed_data.texture_west)
	{
		game->parsed_data.texture_west = ft_dup_ws(tr, 2);
		return (0);
	}
	if (ft_strncmp(tr, "EA ", 3) == 0 && !game->parsed_data.texture_east)
	{
		game->parsed_data.texture_east = ft_dup_ws(tr, 2);
		return (0);
	}
	return (look_one_two(tr, game));
}

int	add_line(t_game *game, char *line, int i)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	game->parsed_data.map[i] = ft_strdup(line);
	if (!game->parsed_data.map[i])
	{
		free(line);
		quity(game, 2, "ligne invalide");
	}
	if (line)
		free(line);
	return (1);
}

int	player_or_sp(char c, t_game *game, int i, int j)
{
	if (c == 'S' || c == 'E' || c == 'N' || c == 'W')
	{
		game->parsed_data.p_num++;
		set_pos(i, j, game);
		return (1);
	}
	else if (c == '0')
		return (1);
	else if (c == '1' || c == ' ' || c == '\n')
		return (0);
	else
		quity(game, -1, "caractère invalide dans la map");
	return (0);
}

int	look_side(char **map, int i, int j, t_game *game)
{
	if (!map || !map[j] || i < 1 || j < 1)
		return (-1);
	if (!str_look(" 1NSWE0\t", map[j + 1][i]))
		quity(game, 2, "map invalide: dessous");
	if (!str_look(" 1NSWE0\t", map[j - 1][i]))
		quity(game, 2, "map invalide: dessus");
	if (!str_look(" 1NSWE0\t", map[j][i + 1]))
		quity(game, 2, "map invalide: droite");
	if (!str_look(" 1NSWE0\t", map[j][i - 1]))
		quity(game, 2, "map invalide: gauche");
	return (0);
}
