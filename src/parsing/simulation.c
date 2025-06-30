#include "cub3d.h"

// Fonction de nettoyage de la mémoire
void	cleanup_parsed_data(t_parsed_data *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (i < data->map_height)
		{
			if (data->map[i])
				free(data->map[i]);
			i++;
		}
		free(data->map);
		data->map = NULL;
	}
	if (data->texture_north)
		free(data->texture_north);
	if (data->texture_south)
		free(data->texture_south);
	if (data->texture_west)
		free(data->texture_west);
	if (data->texture_east)
		free(data->texture_east);
}

// Fonction principale de simulation
int	simulate_parsing(t_parsed_data *data)
{
	printf("Début simulate_parsing\n");
	
	if (!data)
	{
		printf("Erreur: data est NULL\n");
		return (1);
	}
	
	printf("Test init_test_map...\n");
	if (!init_test_map(data))
	{
		printf("Erreur: init_test_map a échoué\n");
		return (1);
	}
	
	printf("Test init_test_player...\n");
	if (!init_test_player(data))
	{
		printf("Erreur: init_test_player a échoué\n");
		cleanup_parsed_data(data);
		return (1);
	}
	
	printf("Test init_test_textures...\n");
	if (!init_test_textures(data))
	{
		printf("Erreur: init_test_textures a échoué\n");
		cleanup_parsed_data(data);
		return (1);
	}
	
	printf("Test init_test_colors...\n");
	if (!init_test_colors(data))
	{
		printf("Erreur: init_test_colors a échoué\n");
		cleanup_parsed_data(data);
		return (1);
	}
	
	printf("Parsing simule avec succes\n");
	return (0);
}

// Initialisation de la carte de test
int init_test_map(t_parsed_data *data)
{
	data->map_height = 5;
	data->map_width = 6;
	
	data->map = malloc(sizeof(char *) * data->map_height);
	if (!data->map)
		return (0);
	
	data->map[0] = ft_strdup("111111");
	data->map[1] = ft_strdup("100001");
	data->map[2] = ft_strdup("101001");
	data->map[3] = ft_strdup("100001");
	data->map[4] = ft_strdup("111111");
	
	return (1);
}

// Initialisation de la position du joueur
int init_test_player(t_parsed_data *data)
{
	data->player_x = 1.5; // Position au centre de la case
	data->player_y = 2.5; // Position au centre de la case
	data->player_orientation = 'N';
	
	// Direction vers le Nord
	data->dir_x = 0.0;
	data->dir_y = -1.0;
	
	// Plan de caméra perpendiculaire à la direction
	// FOV de 66 degrés (0.66 est la longueur du plan)
	data->plane_x = 0.66;
	data->plane_y = 0.0;
	
	return (1);
}

// Initialisation des textures
int init_test_textures(t_parsed_data *data)
{
	data->texture_north = ft_strdup("textures/north.xpm");
	data->texture_south = ft_strdup("textures/south.xpm");
	data->texture_west = ft_strdup("textures/west.xpm");
	data->texture_east = ft_strdup("textures/east.xpm");
	return (1);
}

// Initialisation des couleurs
int init_test_colors(t_parsed_data *data)
{
	data->floor_r = 255;
	data->floor_g = 255;
	data->floor_b = 255;
	data->ceiling_r = 255;
	data->ceiling_g = 255;
	data->ceiling_b = 255;
	return (1);
}
