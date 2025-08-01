/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 23:09:56 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/10 14:43:05 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

// Duplique une chaîne de caractères
char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

void	cleanup_game(t_game *game)
{
	quity(game, 0, "finito");
	cleanup_textures(game);
	if (game->mlx_data.img)
		mlx_destroy_image(game->mlx_data.mlx, game->mlx_data.img);
	if (game->mlx_data.win)
		mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
	if (game->mlx_data.mlx)
		mlx_destroy_display(game->mlx_data.mlx);
	free_map(game);
}
