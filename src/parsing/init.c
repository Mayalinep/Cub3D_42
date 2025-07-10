/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:59:05 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/10 15:35:01 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_floor_cell(char *line, t_game *game, char *c, int i)
{
	char	**tab;
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
				(free(line), free_tab(tab), quity(game, -1,
						"Color format error: non-digit found"));
			j++;
		}
		i++;
	}
	if (color_assignation(game, tab, c) == 1)
		(free(line), free_tab(tab), quity(game, -1, "Color number error"));
	(free(line), free_tab(tab));
}

char	*ft_dup_ws(char *line, int i)
{
	int		start;
	int		end;
	char	*str;

	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	end = ft_strlen(line) - 1;
	while (end > start && (line[end] == '\n'
			|| line[end] == ' ' || line[end] == '\t'))
		end--;
	str = ft_substr(line, start, end - start + 1);
	free(line);
	return (str);
}

static void	reset_pos(t_game *game)
{
	game->parsed_data.dir_x = game->parsed_data.dir_x * -1;
	game->parsed_data.dir_y = game->parsed_data.dir_y * -1;
	game->parsed_data.plane_x = game->parsed_data.plane_x * -1;
	game->parsed_data.plane_y = game->parsed_data.plane_y * -1;
}

void	set_pos(int i, int j, t_game *game)
{
	game->parsed_data.player_x = i;
	game->parsed_data.player_y = j;
	if (game->parsed_data.map[j][i] == 'N'
		|| game->parsed_data.map[j][i] == 'S')
	{
		game->parsed_data.dir_x = 0;
		game->parsed_data.dir_y = -1;
		game->parsed_data.plane_x = 0.66;
		game->parsed_data.plane_y = 0;
		if (game->parsed_data.map[j][i] == 'S')
			reset_pos(game);
	}
	else if (game->parsed_data.map[j][i] == 'E'
		|| game->parsed_data.map[j][i] == 'W')
	{
		game->parsed_data.dir_x = 1;
		game->parsed_data.dir_y = 0;
		game->parsed_data.plane_x = 0;
		game->parsed_data.plane_y = 0.66;
		if (game->parsed_data.map[j][i] == 'W')
			reset_pos(game);
	}
}
