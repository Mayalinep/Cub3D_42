/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 22:17:28 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/04 22:29:12 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	color_assignation(t_game *game, char **tab, char *c)
{
	if (c[0] == 'F')
	{
		game->parsed_data.floor_r = atol(tab[0]);
		game->parsed_data.floor_g = atol(tab[1]);
		game->parsed_data.floor_b = atol(tab[2]);
		if (game->parsed_data.floor_b > 255 || game->parsed_data.floor_g > 255
			|| game->parsed_data.floor_r > 255)
			return (1);
	}
	if (c[0] == 'C')
	{
		game->parsed_data.ceiling_r = atol(tab[0]);
		game->parsed_data.ceiling_g = atol(tab[1]);
		game->parsed_data.ceiling_b = atol(tab[2]);
		if (game->parsed_data.ceiling_b > 255
			|| game->parsed_data.ceiling_g > 255
			|| game->parsed_data.ceiling_r > 255)
			return (1);
	}
	return (0);
}

char	**sp_and_trimm(char *line, t_game *game, char **tab, char *c)
{
	char	*res;

	tab = ft_split(line, ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2] || tab[3])
		(free(line), free_tab(tab), quity(game, -1, "Color problem"));
	res = ft_strtrim(tab[0], c);
	free(tab[0]);
	tab[0] = res;
	if (!tab[0])
		(free(line), free_tab(tab), quity(game, -1,
				"Memory allocation failed (strtrim)"));
	return (tab);
}

int	look_zero(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '0' && ft_isdigit(tab[i][1]))
			return (1);
		i++;
	}
	return (0);
}
