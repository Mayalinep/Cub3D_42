#include "cub3d.h"

// Fonction principale de simulation
int simulate_parsing(t_parsed_data *data)
{
    printf("Début simulate_parsing\n");
    
    if (!data)
    {
        printf("Erreur: data est NULL\n");
        return (0);
    }
    
    printf("Test init_test_map...\n");
    if (!init_test_map(data))
    {
        printf("Erreur: init_test_map a échoué\n");
        return (0);
    }
    
    printf("Test init_test_player...\n");
    if (!init_test_player(data))
    {
        printf("Erreur: init_test_player a échoué\n");
        return (0);
    }
    
    printf("Test init_test_textures...\n");
    if (!init_test_textures(data))
    {
        printf("Erreur: init_test_textures a échoué\n");
        return (0);
    }
    
    printf("Test init_test_colors...\n");
    if (!init_test_colors(data))
    {
        printf("Erreur: init_test_colors a échoué\n");
        return (0);
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
    data->player_x = 1.0;
    data->player_y = 2.0;
    data->player_orientation = 'N';
    data->dir_x = 0.0;
    data->dir_y = -1.0;
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
