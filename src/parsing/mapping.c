/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:31:38 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/08 13:34:59 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*k_spaces(char *line)
{
	int	i;
	int	j;

	if (!line)
		return (NULL);
	i = 0;
	j = ft_strlen(line) - 1;
	while ((line[i] == '\t' || line[i] == ' ') && line[i])
		i++;
	while ((line[j] == '\t' || line[j] == ' ') && j > i)
		j--;
	// free(line);
	return (ft_substr(line, i, j - i + 1));
}

int	look_one(char *line, t_game *game)
{
	char	*tr;

	tr = k_spaces(line);
	if (ft_strncmp(tr, "SO ", 3) == 0 && game->parsed_data.texture_south == NULL)
	{
		game->parsed_data.texture_south = ft_dup_ws(tr, 2);
		return (0);
	}
	if (ft_strncmp(tr, "NO ", 3) == 0 && game->parsed_data.texture_north == NULL)
	{
		game->parsed_data.texture_north = ft_dup_ws(tr, 2);
		return (0);
	}
	if (ft_strncmp(tr, "WE ", 3) == 0 && game->parsed_data.texture_west == NULL)
	{
		game->parsed_data.texture_west = ft_dup_ws(tr, 2);
		return (0);
	}
	if (ft_strncmp(tr, "EA ", 3) == 0 && game->parsed_data.texture_east == NULL)
	{
		game->parsed_data.texture_east = ft_dup_ws(tr, 2);
		return (0);
	}
	return (look_one_two(tr, game));
}

int	look_one_two(char *line, t_game *game)
{
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "F", 1) == 0)
		return (set_floor_cell(line, game, "F ", 0), 0);
	if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "C", 2) == 0)
		return (set_floor_cell(line, game, "C ", 0), 0);
	free(line);
	return (1);
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
	{
		printf("%s a i = %i et j = %i\n", game->parsed_data.map[i], i, j);
		quity(game, -1, "caractère invalide dans la map");
	}
	return (0);
}


void	pad_map_lines(char **map)
{
	int		i;
	size_t	max_len;
	size_t	len;

	i = 0;
	max_len = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < max_len)
		{
			char *new_line = malloc(max_len + 1);
			if (!new_line)
				return ;
			ft_memcpy(new_line, map[i], len);
			ft_memset(new_line + len, '\0', max_len - len);
			new_line[max_len] = '\0';
			free(map[i]);
			map[i] = new_line;
		}
		i++;
	}
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


int	str_look(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*verif_xpm(char *xpm)
{
	int	i;
	int	fd;
	char *str;

	str = ft_strdup(xpm + 2);
	i = ft_strlen(xpm) - 1;
	fd = -1;
	while (xpm[i] == '\t' || xpm[i] == ' ')
		i--;
	if (xpm[i--] != 'm')
		return (free(xpm), NULL);
	if (xpm[i--] != 'p')
		return (free(xpm), NULL);
	if (xpm[i--] != 'x')
		return (free(xpm), NULL);
	if (xpm[i--] != '.')
		return (free(xpm), NULL);
	fd = open(xpm, O_RDONLY);
	if (fd == -1)
		return (free(xpm), NULL);
	close(fd);
	free(xpm);
	return (str);
}
