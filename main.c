#include "cub3d.h"

// Fonction pour initialiser la minilibx
int	init_mlx(t_mlx_data *mlx_data)
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
int	handle_keypress(int keycode, t_game *game)
{
	double	speed;

	speed = 0.1;
	if (keycode == KEY_W)
	{
		game->parsed_data.player_x += game->parsed_data.dir_x * speed;
		game->parsed_data.player_y += game->parsed_data.dir_y * speed;
	}
	if (keycode == KEY_S)
	{
		game->parsed_data.player_x -= game->parsed_data.dir_x * speed;
		game->parsed_data.player_y -= game->parsed_data.dir_y * speed;
	}
	if (keycode == KEY_A || keycode == KEY_D)
		keypress_rotation(keycode, game);
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
		exit(0);
	}
	return (0);
}
// Fonction pour gerer la rotation du joueur
int	keypress_rotation(int keycode, t_game *game)
{
	double	old_dir_x;
	double	old_dir_y;
	double	old_plane_x;
	double	angle;

	old_dir_x = game->parsed_data.dir_x;
	old_dir_y = game->parsed_data.dir_y;
	old_plane_x = game->parsed_data.plane_x;
	if (keycode == KEY_A)
	{
		angle = -0.1;
			// Rotation a gauche (negatif car on tourne dans le sens des aiguilles d'une montre)
		game->parsed_data.dir_x = old_dir_x * cos(angle) - old_dir_y
			* sin(angle);
		game->parsed_data.dir_y = old_dir_x * sin(angle) + old_dir_y
			* cos(angle);
		game->parsed_data.plane_x = old_plane_x * cos(angle)
			- game->parsed_data.plane_y * sin(angle);
		game->parsed_data.plane_y = old_plane_x * sin(angle)
			+ game->parsed_data.plane_y * cos(angle);
	}
	if (keycode == KEY_D)
	{
		angle = 0.1;
			// Rotation a droite (positif car on tourne dans le sens inverse des aiguilles d'une montre)
		game->parsed_data.dir_x = old_dir_x * cos(angle) - old_dir_y
			* sin(angle);
		game->parsed_data.dir_y = old_dir_x * sin(angle) + old_dir_y
			* cos(angle);
		game->parsed_data.plane_x = old_plane_x * cos(angle)
			- game->parsed_data.plane_y * sin(angle);
		game->parsed_data.plane_y = old_plane_x * sin(angle)
			+ game->parsed_data.plane_y * cos(angle);
	}
	return (0);
}

// Fonction pour gerer la fermeture de la fenetre
int	handle_close(t_game *game)
{
	mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
	exit(0);
}
// Fonction principale
int	main(void)
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
	mlx_hook(game.mlx_data.win, 2, 1L << 0, handle_keypress, &game);
		// 2 = evenement de touche, 1L << 0 = touche pressee,
		handle_keypress = fonction a appeler lors de l evenement,
		&data = donnees a passer a la fonction
	mlx_hook(game.mlx_data.win, 17, 1L << 17, handle_close, &game); 
		// 17 = evenement de fermeture de la fenetre,
		1L << 17 = fermeture de la fenetre,
		handle_close = fonction a appeler lors de l evenement,
		&data = donnees a passer a la fonction
	mlx_loop(game.mlx_data.mlx);                                    
		// Boucle principale de la minilibx
	return (0);
}