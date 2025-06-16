#ifndef MLX_H
#define MLX_H

#define KEY_W 119 //touche w, pour avancer
#define KEY_A 97 //touche a, pour reculer
#define KEY_S 115 //touche s, pour aller a gauche
#define KEY_D 100 //touche d, pour aller a droite
#define KEY_ESC 65307 //touche esc, pour quitter le jeu


typedef struct s_mlx_data
{
    void *mlx; //Poiteur sur la connexion a la minilibx
    void *win; //Poiteur sur la fenetre creee par minilibx
    void *img; //Poiteur sur l'image (pour dessiner en memoire avant d afficher)
    char *addr; //Poiteur sur l'adresse de l'image ( du debut de l image) pour pouvoir modifier les pixels
    int bits_per_pixel; //Nombre de bits par pixel
    int line_length; //Nombre de octets par ligne de l'image (utilie pour naviguer dans l'image)
    int endian; //Ordre des octets dans la memoire (0 pour petit endian, 1 pour grand endian)
} t_mlx_data;


#endif