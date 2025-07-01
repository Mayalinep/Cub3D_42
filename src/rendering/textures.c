/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:37:15 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/30 15:15:04 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "cub3d.h"

// Fonction pour charger une texture XPM
int	load_texture(void *mlx, t_img *texture, char *path)
{
	int	width;
	int	height;

	printf("Debug: Tentative de chargement de la texture: '%s'\n", path);
	texture->img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!texture->img)
	{
		printf("Erreur: Impossible de charger la texture %s\n", path);
		return (0);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->addr)
	{
		printf("Erreur: Impossible d'obtenir l'adresse de la texture %s\n", path);
		mlx_destroy_image(mlx, texture->img);
		return (0);
	}
	printf("Debug: Texture '%s' chargée avec succès\n", path);
	return (1);
}

// Fonction pour charger toutes les textures
int	load_all_textures(t_game *game)
{
	char	*texture_paths[4];

	texture_paths[NORTH] = game->parsed_data.texture_north;
	texture_paths[EAST] = game->parsed_data.texture_east;
	texture_paths[SOUTH] = game->parsed_data.texture_south;
	texture_paths[WEST] = game->parsed_data.texture_west;
	
	if (!load_texture(game->mlx_data.mlx, &game->textures.tex[NORTH], texture_paths[NORTH]))
		return (0);
	if (!load_texture(game->mlx_data.mlx, &game->textures.tex[EAST], texture_paths[EAST]))
		return (0);
	if (!load_texture(game->mlx_data.mlx, &game->textures.tex[SOUTH], texture_paths[SOUTH]))
		return (0);
	if (!load_texture(game->mlx_data.mlx, &game->textures.tex[WEST], texture_paths[WEST]))
		return (0);
	
	game->textures.loaded = 1;
	printf("Toutes les textures ont été chargées avec succès\n");
	return (1);
}

// Fonction pour obtenir la couleur d'un pixel de texture
int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || y < 0 || x >= 64 || y >= 64)
		return (0);
	pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	color = *(int*)pixel;
	return (color);
}

// Fonction pour nettoyer les textures
void	cleanup_textures(t_game *game)
{
	int	i;

	if (game->textures.loaded)
	{
		i = 0;
		while (i < 4)
		{
			if (game->textures.tex[i].img)
				mlx_destroy_image(game->mlx_data.mlx, game->textures.tex[i].img);
			i++;
		}
		game->textures.loaded = 0;
	}
} 