#ifndef MLX_H
#define MLX_H

#define KEY_W 119 //touche w, pour avancer
#define KEY_A 97 //touche a, pour reculer
#define KEY_S 115 //touche s, pour aller a gauche
#define KEY_D 100 //touche d, pour aller a droite
#define KEY_LEFT 65361 //touche fleche gauche, deplacement perpendiculaire a la direction du joueur
#define KEY_RIGHT 65363 //touche fleche droite, deplacement perpendiculaire a la direction du joueur
#define KEY_ESC 65307 //touche esc, pour quitter le jeu
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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


#endif