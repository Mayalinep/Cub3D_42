/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:31:38 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/04 14:46:27 by ssoukoun         ###   ########.fr       */
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

int	color_assignation(t_game *game, char **tab, char *c)
{
	if (c[0] == 'F')
	{
		game->parsed_data.floor_r = atol(tab[0]);
		game->parsed_data.floor_g = atol(tab[1]);
		game->parsed_data.floor_b = atol(tab[2]);
		if (game->parsed_data.floor_b > 255 || game->parsed_data.floor_g > 255 || game->parsed_data.floor_r > 255)
			return (1);
	}
	if (c[0] == 'C')
	{
		game->parsed_data.ceiling_r = atol(tab[0]);
		game->parsed_data.ceiling_g = atol(tab[1]);
		game->parsed_data.ceiling_b = atol(tab[2]);
		if (game->parsed_data.ceiling_b > 255 || game->parsed_data.ceiling_g > 255 || game->parsed_data.ceiling_r > 255)
			return (1);
	}
	return (0);
}

char **sp_and_trimm(char *line, t_game *game, char **tab, char *c)
{
	char	*res;

	tab = ft_split(line, ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2] || tab[3])
		(free(line),free_tab(tab),quity(game, -1, "Color problem"));

	res = ft_strtrim(tab[0], c);
	free(tab[0]);
	tab[0] = res;
	if (!tab[0])
		(free(line), free_tab(tab), quity(game, -1, "Memory allocation failed (strtrim)"));
	return (tab);
	
}

int	look_zero(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '0' && ft_isdigit(tab[i][1]))
			return(1);
		i++;
	}
	return (0);
}
void	set_floor_cell(char *line, t_game *game, char *c)
{
	char	**tab;
	int		i;
	int		j;

	if (!line)
		return ;
	tab = NULL;
	tab = sp_and_trimm(line, game, tab, c);
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (look_zero(tab))
				(free(line), free_tab(tab), quity(game, -1, "les 0 mgl"));
			if (!ft_isdigit(tab[i][j]) && tab[i][j] != '\n')
				(free(line), free_tab(tab), quity(game, -1, "Color format error: non-digit found"));
			j++;
		}
		i++;
	}
	if (color_assignation(game, tab, c) == 1)
		(free(line), free_tab(tab), quity(game, -1, "Color number error"));
	(free(line), free_tab(tab));
}


void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
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
		return (set_floor_cell(line, game, "F "), 0);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (set_floor_cell(line, game, "C "), 0);
	return (1);
}

char	*ft_dup_ws(char *line, int i)
{
	char	*str;
	int		len;

	// Ignorer les espaces après le préfixe (NO, SO, etc.)
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	
	// Dupliquer tout le reste (le chemin complet)
	str = ft_strdup(line + i);
	len = ft_strlen(str);
	
	// Enlever le \n à la fin s'il existe
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	
	free(line);
	return (str);
}
