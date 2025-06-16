#include "cub3d.h"

//Fonction pour initialiser la minilibx
int init_mlx(t_mlx_data *mlx_data)
{
    mlx_data->mlx = mlx_init(); // Initialisation de la minilibx
    if (mlx_data->mlx == NULL)
    {
        printf("Erreur lors de l'initialisation de la minilibx\n");
        return (1);
    }
    mlx_data->win = mlx_new_window(mlx_data->mlx, 1000, 1000, "Cub3D");
    if (mlx_data->win == NULL)
    {   
        printf("Erreur lors de la creation de la fenetre\n");
        return (1);
    }
    mlx_data->img = mlx_new_image(mlx_data->mlx, 1000, 1000);
    if (mlx_data->img == NULL)
    {
        printf("Erreur lors de la creation de l'image\n");
        return (1);
    }
    return (0);
}
int handle_keypress(int keycode, t_game *game)
{
    if (keycode == KEY_W)
    {
        game->parsed_data.player_y -= 1;
    }
    if (keycode == KEY_A)
    {
        game->parsed_data.player_x -= 1;
    }
    if (keycode == KEY_S)
    {
        game->parsed_data.player_y += 1;
    }
    if (keycode == KEY_D)
    {
        game->parsed_data.player_x += 1;
    }
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
        exit(0);
    }
    return (0);
}
//Fonction pour gerer la fermeture de la fenetre
int handle_close(t_game *game)
{
    mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
    exit(0);
}
//Fonction principale
int main(void)
{
    t_game game;
    if (simulate_parsing(&game.parsed_data) != 0)
    {
        printf("Erreur lors du parsing\n");
        return (1);
    }
    if (init_mlx(&game.mlx_data) != 0)
    {
        printf("Erreur lors de l'initialisation de la minilibx\n");
        return (1);
    }
    mlx_hook(game.mlx_data.win, 2, 1L << 0, handle_keypress, &game); // 2 = evenement de touche, 1L << 0 = touche pressee, handle_keypress = fonction a appeler lors de l evenement, &data = donnees a passer a la fonction
    mlx_hook(game.mlx_data.win, 17, 1L << 17, handle_close, &game); // 17 = evenement de fermeture de la fenetre, 1L << 17 = fermeture de la fenetre, handle_close = fonction a appeler lors de l evenement, &data = donnees a passer a la fonction
    mlx_loop(game.mlx_data.mlx); // Boucle principale de la minilibx
    return (0);
}