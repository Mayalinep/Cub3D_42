#ifndef CUB3D_H
#define CUB3D_H

#include "mlx.h"
#include <stdlib.h>
#include <string.h>

typedef struct s_game
{
    t_parsed_data parsed_data;
    t_mlx_data mlx_data;
} t_game;

// Structure pour stocker les données parsées
typedef struct s_parsed_data
{
    // Dimensions de la carte
    int map_height;
    int map_width;
    char **map;
    
    // Position et orientation du joueur
    double  player_x;
    double player_y;
    char player_orientation;

    //Vecteurs de direction et plan de camera
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    
    // Chemins des textures
    char *texture_north;
    char *texture_south;
    char *texture_west;
    char *texture_east;
    
    // Couleurs du sol et du plafond (RGB)
    int floor_r;
    int floor_g;
    int floor_b;
    int ceiling_r;
    int ceiling_g;
    int ceiling_b;
} t_parsed_data;

// Prototypes des fonctions de simulation
int simulate_parsing(t_parsed_data *data);
int init_test_map(t_parsed_data *data);
int init_test_player(t_parsed_data *data);
int init_test_textures(t_parsed_data *data);
int init_test_colors(t_parsed_data *data);

// Fonctions utilitaires
char *ft_strdup(const char *s);

#endif