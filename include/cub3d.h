#ifndef CUB3D_H
#define CUB3D_H

#include "mlx.h"
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>

// Définitions des touches du clavier
#define KEY_W 119 //touche w, pour avancer
#define KEY_A 97 //touche a, pour reculer
#define KEY_S 115 //touche s, pour aller a gauche
#define KEY_D 100 //touche d, pour aller a droite
#define KEY_LEFT 65361 //touche fleche gauche, deplacement perpendiculaire a la direction du joueur
#define KEY_RIGHT 65363 //touche fleche droite, deplacement perpendiculaire a la direction du joueur
#define KEY_ESC 65307 //touche esc, pour quitter le jeu
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Définitions des directions des textures (inspiré du code de référence)
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// Définitions des couleurs des murs
#define WALL_NORTH_COLOR 0x404040  // Gris foncé
#define WALL_SOUTH_COLOR 0x606060  // Gris moyen
#define WALL_EAST_COLOR  0x808080  // Gris clair
#define WALL_WEST_COLOR  0x505050  // Gris intermédiaire

// Définition pour le parsing
#define MAX_MAP_LINES 100

typedef struct s_mlx_data
{
    void *mlx; //Poiteur sur la connexion a la minilibx
    void *win; //Pointeur sur la fenetre creee par minilibx
    void *img; //Pointeur sur l'image (pour dessiner en memoire avant d afficher)
    char *addr; //Pointeur sur l'adresse de l'image ( du debut de l image) pour pouvoir modifier les pixels
    int bits_per_pixel; //Nombre de bits par pixel
    int line_length; //Nombre de octets par ligne de l'image (utilie pour naviguer dans l'image)
    int endian; //Ordre des octets dans la memoire (0 pour petit endian, 1 pour grand endian)
} t_mlx_data;

typedef struct s_keys
{
    int w_press;
    int a_press;
    int s_press;
    int d_press;
    int l_press;
    int r_press;
} t_keys;

//Structure pour stocker les données parsées
typedef struct s_parsed_data
{
    // Dimensions de la carte
    int map_height;
    int map_width;
    char **map;
    
    // Ajouts pour le parsing
    int file;    // file descriptor
    int p_num;   // nombre de joueurs trouvés
    
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

typedef struct s_raycasting
{
	double delta_dist_x; //distance pour traverser une case en x
	double delta_dist_y; //distance pour traverser une case en y
	int step_x; //sens du rayon en x
	int step_y; //sens du rayon en y
	int map_x; //coordonnée x de la case en cours
	int map_y; //coordonnée y de la case en cours
	int hit; // 0 = pas de mur touché, 1 = mur touché
	int side; // 0 = mur vertical (X), 1 = mur horizontal (Y)
    double side_dist_x; // distance entre le joueur et la prochaine ligne verticale
    double side_dist_y; // distance entre le joueur et la prochaine ligne horizontale
	double wall_x; // position X sur le mur pour les textures 
} t_raycasting;

// Structure pour les images (inspirée du code de référence)
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_textures
{
	t_img	tex[4];  // [0] = NORTH, [1] = EAST, [2] = SOUTH, [3] = WEST
	int		loaded; // 1 si les textures sont chargées, 0 sinon
}	t_textures;

typedef struct s_game
{
    t_parsed_data parsed_data;
	t_raycasting raycasting;
    t_mlx_data mlx_data;
    t_keys keys;
	t_textures textures;
} t_game;

// Prototypes des fonctions de simulation
int simulate_parsing(t_parsed_data *data);
int init_test_map(t_parsed_data *data);
int init_test_player(t_parsed_data *data);
int init_test_textures(t_parsed_data *data);
int init_test_colors(t_parsed_data *data);

// Fonctions MLX et input
int init_mlx(t_mlx_data *mlx_data);
int init_keys(t_keys *keys);
int handle_keypress(int keycode, t_game *game);
int handle_keyrelease(int keycode, t_game *game);
int handle_close(t_game *game);
int wall_collision(double new_x, double new_y, t_parsed_data *data);
int try_move(t_game *game, double dir_x, double dir_y);
int keypress_rotation(int keycode, t_game *game);
int update_player(t_game *game);

// Fonctions raycasting
int ray_casting(t_game *game);
void calculate_ray_direction(int x, t_game *game, double *ray_dir_x, double *ray_dir_y);
double find_wall_distance(double ray_dir_x, double ray_dir_y, t_game *game);
double calculate_delta_dist_x(double ray_dir_x);
double calculate_delta_dist_y(double ray_dir_y);
void ray_orientation(double ray_dir_x, double ray_dir_y, int *step_x, int *step_y);
int calculate_line_height(double distance);
void dda_loop(t_game *game);
double calculate_final_distance(double ray_dir_x, double ray_dir_y, t_game *game);
void calculate_wall_x(double ray_dir_x, double ray_dir_y, double distance, t_game *game);

// Fonctions utilitaires
char *ft_strdup(const char *s);
void cleanup_parsed_data(t_parsed_data *data);
void cleanup_game(t_game *game);
void init_textures(t_textures *textures);

// Nouvelles fonctions de parsing
void init_game(t_game *game, int ac, char **av);
int verif_part_one(int ac, char **av, t_game *game);
void verif_part_two(t_game *game);
int look_one(char *line, t_game *game);
int look_side(char **map, int i, int j, t_game *game);
void get_map(int file, t_game *game);
int add_line(t_game *game, char *line, int i);
char *ft_dup_ws(char *line, int i);
void set_floor_cell(char *line, t_game *game, char c);

// Nouvelles fonctions utilitaires manquantes
int ft_strlen(const char *str);
int ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_isdigit(int c);
char **ft_split(char const *s, char c);
void *ft_calloc(size_t nmemb, size_t size);
char *ft_substr(char const *s, unsigned int start, size_t len);
long atol(const char *str);
void print_map(char **map);
void print_all(t_game *game);

// Fonctions de nettoyage adaptées à ta structure
void quity(t_game *game, int j, char *str);
void free_map(t_game *game);
void free_mlx(t_game *game);

// Fonctions de gestion des textures
int load_texture(void *mlx, t_img *texture, char *path);
int load_all_textures(t_game *game);
int get_texture_pixel(t_img *texture, int x, int y);
void cleanup_textures(t_game *game);

#endif