/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:31:38 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/27 19:22:36 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	}
	while (game->parsed_data.map[--i] && game->parsed_data.map[i][0] == '\n')
	{
		free(game->parsed_data.map[i]);
		game->parsed_data.map[i] = NULL;
	}
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

void	set_floor_cell(char *line, t_game *game, char c)
{
	char	**tab;
	int		i;

	if (!line)
		return ;
	i = 0;
	tab = ft_split(line, ',');
	if (c == 'F')
	{
		game->parsed_data.floor_r = atol(tab[0]);
		game->parsed_data.floor_g = atol(tab[1]);
		game->parsed_data.floor_b = atol(tab[2]);
	}
	if (c == 'C')
	{
		game->parsed_data.ceiling_r = atol(tab[0]);
		game->parsed_data.ceiling_g = atol(tab[1]);
		game->parsed_data.ceiling_b = atol(tab[2]);
	}
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	(free(line), free(tab));
}

int	look_one(char *line, t_game *game)
{
	if (ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "S ", 2) == 0)
		return (game->parsed_data.texture_south = ft_dup_ws(line, 2), 0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "N ", 2) == 0)
		return (game->parsed_data.texture_north = ft_dup_ws(line, 2), 0);
	if (ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "W ", 2) == 0)
		return (game->parsed_data.texture_west = ft_dup_ws(line, 2), 0);
	if (ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "E ", 2) == 0)
		return (game->parsed_data.texture_east = ft_dup_ws(line, 2), 0);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (set_floor_cell(line, game, 'F'), 0);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (set_floor_cell(line, game, 'C'), 0);
	return (1);
}

char	*ft_dup_ws(char *line, int i)
{
	char	*str;
	int		len;

	while (line[i] != '.' && line[i] && ft_isdigit(line[i]) == 0)
		i++;
	str = ft_strdup(line + i);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	free(line);
	return (str);
}
