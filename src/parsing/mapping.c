/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:31:38 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/04 22:30:25 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	look_one(char *line, t_game *game)
{
	int	i;

	if (ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "S ", 2) == 0)
		return (game->parsed_data.texture_south = verif_xpm(ft_dup_ws(line, 2),
				&i), 0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "N ", 2) == 0)
		return (game->parsed_data.texture_north = verif_xpm(ft_dup_ws(line, 2),
				&i), 0);
	if (ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "W ", 2) == 0)
		return (game->parsed_data.texture_west = verif_xpm(ft_dup_ws(line, 2),
				&i), 0);
	if (ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "E ", 2) == 0)
		return (game->parsed_data.texture_east = verif_xpm(ft_dup_ws(line, 2),
				&i), 0);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (set_floor_cell(line, game, "F ", 0), 0);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (set_floor_cell(line, game, "C ", 0), 0);
	return (1);
}

int	add_line(t_game *game, char *line, int i)
{
	game->parsed_data.map[i] = ft_strdup(line);
	if (!game->parsed_data.map[i])
	{
		free(line);
		quity(game, 2, "ligne invalide");
	}
	free(line);
	return (1);
}

int	player_or_sp(char c, t_game *game, int i, int j)
{
	if (c == ' ')
		look_side(game->parsed_data.map, i, j, game);
	else if (c != 'S' && c != 'E' && c != 'N' && c != 'W' && c != '0'
		&& c != '1' && c != '\n')
	{
		printf("%s = 0\n", game->parsed_data.map[j]);
		quity(game, -1, "char invalide");
	}
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
	if (map[j + 1][i] != '0' && map[j + 1][i] != '1' && map[j + 1][i] != 'N'
		&& map[j + 1][i] != ' ')
		quity(game, 2, "map invalide");
	if (map[j - 1][i] != '0' && map[j - 1][i] != '1' && map[j - 1][i] != 'N'
		&& map[j - 1][i] != ' ')
		quity(game, 2, "map invalide");
	if ((int)ft_strlen(map[j]) <= i + 1)
		quity(game, 2, "map invalide");
	if (map[j][i + 1] != '0' && map[j][i + 1] != '1' && map[j][i + 1] != 'N'
		&& map[j][i + 1] != ' ')
		quity(game, 2, "map invalide");
	if (i >= (int)ft_strlen(map[j]) || i <= 0)
		quity(game, 2, "map invalide");
	if (map[j][i - 1] != '0' && map[j][i - 1] != '1' && map[j][i - 1] != 'N'
		&& map[j][i - 1] != ' ')
		quity(game, 2, "map invalide");
	return (0);
}

char	*verif_xpm(char *xpm, int *fl)
{
	int	i;
	int	fd;

	i = ft_strlen(xpm) - 1;
	fd = -1;
	if (xpm[i--] != 'm')
		return (fl++, NULL);
	if (xpm[i--] != 'p')
		return (NULL);
	if (xpm[i--] != 'x')
		return (NULL);
	if (xpm[i--] != '.')
		return (NULL);
	fd = open(xpm, O_RDONLY);
	if (fd == -1)
		return (NULL);
	close(fd);
	return (xpm);
}
