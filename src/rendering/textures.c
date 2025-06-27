/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:01:47 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/27 19:32:07 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void *load_texture(t_game *game, char *path, int *width, int *height)
{
	return (mlx_xpm_file_to_image(game->mlx_data.mlx, path, width, height));
}
void	load_all_textures(t_game *game)
{
	printf("DEBUG: Chargement des textures...\n");
	printf("DEBUG: NO = %s\n", game->parsed_data.texture_north);
	printf("DEBUG: SO = %s\n", game->parsed_data.texture_south);
	printf("DEBUG: WE = %s\n", game->parsed_data.texture_west);
	printf("DEBUG: EA = %s\n", game->parsed_data.texture_east);
	
	game->textures.north_img = load_texture(game, game->parsed_data.texture_north, &game->textures.width, &game->textures.height);
	game->textures.south_img = load_texture(game, game->parsed_data.texture_south, &game->textures.width, &game->textures.height);
	game->textures.west_img = load_texture(game, game->parsed_data.texture_west, &game->textures.width, &game->textures.height);
	game->textures.east_img = load_texture(game, game->parsed_data.texture_east, &game->textures.width, &game->textures.height);
	if (game->textures.north_img == NULL || game->textures.south_img == NULL || game->textures.west_img == NULL || game->textures.east_img == NULL)
	{
		printf("Error\nFailed to load textures\n");
		exit(1);
	}
	return;
}

int get_texture_pixel_optimized(int x, int y, char *tex_data, t_game *game)
{
	char *pixel_addr;
	int tex_bpp, tex_line_length, tex_endian;
	
	// Récupérer les infos de la texture (pas de l'image principale)
	mlx_get_data_addr(game->textures.north_img, &tex_bpp, &tex_line_length, &tex_endian);
	
	pixel_addr = tex_data + (y * tex_line_length + 
		x * (tex_bpp / 8));
	return (*(int*)pixel_addr);
}

int get_texture_pixel(void *texture, int x, int y, t_game *game)
{
	char *tex_data;
	char *pixel_addr;
	
	tex_data = mlx_get_data_addr(texture, &game->mlx_data.bits_per_pixel, &game->mlx_data.line_length, &game->mlx_data.endian);
	pixel_addr = tex_data + (y * game->mlx_data.line_length + 
    x * (game->mlx_data.bits_per_pixel / 8));
	return (*(int*)pixel_addr);
}

void *get_wall_texture(t_game *game)
{
	if (game->raycasting.side == 0)
	{
		if (game->raycasting.step_x > 0)
			return (game->textures.east_img);
		else
			return (game->textures.west_img);
	}
	else
	{
		if (game->raycasting.step_y > 0)
			return (game->textures.south_img);
		else
			return (game->textures.north_img);
	}
	return (NULL);
}