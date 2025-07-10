/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:01:52 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/10 15:27:09 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// Définitions des touches du clavier
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define SENSITIVITY 0.002

// Définitions des directions des textures (inspiré du code de référence)
# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

// Définitions des couleurs des murs
# define WALL_NORTH_COLOR 0x404040
# define WALL_SOUTH_COLOR 0x606060
# define WALL_EAST_COLOR 0x808080
# define WALL_WEST_COLOR 0x505050

// Définition pour le parsing
# define MAX_MAP_LINES 100
# define MAX_MAP_LEN 100

typedef struct s_mlx_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_mlx_data;

typedef struct s_keys
{
	int				w_press;
	int				a_press;
	int				s_press;
	int				d_press;
	int				l_press;
	int				r_press;
}					t_keys;

// Structure pour stocker les données parsées
typedef struct s_parsed_data
{
	int				map_height;
	int				map_width;
	char			**map;
	int				file;
	int				p_num;
	double			player_x;
	double			player_y;
	char			player_orientation;

	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;

	char			*texture_north;
	char			*texture_south;
	char			*texture_west;
	char			*texture_east;

	int				floor_r;
	int				floor_g;
	int				floor_b;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;
}					t_parsed_data;

typedef struct s_raycasting
{
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				map_x;
	int				map_y;
	int				hit;
	int				side;
	double			side_dist_x;
	double			side_dist_y;
	double			wall_x;
}					t_raycasting;

// Structure pour les images (inspirée du code de référence)
typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_textures
{
	t_img			tex[4];
	int				loaded;
}					t_textures;

typedef struct s_game
{
	t_parsed_data	parsed_data;
	t_raycasting	raycasting;
	t_mlx_data		mlx_data;
	t_keys			keys;
	t_textures		textures;
}					t_game;

// Fonctions MLX et input
int					init_mlx(t_mlx_data *mlx_data);
int					init_keys(t_keys *keys);
int					handle_keypress(int keycode, t_game *game);
int					handle_keyrelease(int keycode, t_game *game);
int					handle_close(t_game *game);
int					wall_collision(double new_x, double new_y,
						t_parsed_data *data);
int					try_move(t_game *game, double dir_x, double dir_y);
int					keypress_rotation(int keycode, t_game *game);
void				rotate_player(double angle, t_game *game);
int					update_player(t_game *game);

// Fonctions raycasting
int					ray_casting(t_game *game);
void				calculate_ray_direction(int x, t_game *game,
						double *ray_dir_x, double *ray_dir_y);
double				find_wall_distance(double ray_dir_x, double ray_dir_y,
						t_game *game);
double				calculate_delta_dist_x(double ray_dir_x);
double				calculate_delta_dist_y(double ray_dir_y);
void				ray_orientation(double ray_dir_x, double ray_dir_y,
						int *step_x, int *step_y);
int					calculate_line_height(double distance);
void				dda_loop(t_game *game);
double				calculate_final_distance(double ray_dir_x, double ray_dir_y,
						t_game *game);
void				calculate_wall_x(double ray_dir_x, double ray_dir_y,
						double distance, t_game *game);

// Fonctions utilitaires
char				*ft_strdup(const char *s);
void				cleanup_parsed_data(t_parsed_data *data);
void				cleanup_game(t_game *game);
void				init_textures(t_textures *textures);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);

// Nouvelles fonctions de parsing
void				init_game(t_game *game, int ac, char **av);
int					verif_part_one(int ac, char **av, t_game *game);
void				verif_part_two(t_game *game);
int					look_one(char *line, t_game *game);
int					look_side(char **map, int i, int j, t_game *game);
void				get_map(int file, t_game *game);
int					add_line(t_game *game, char *line, int i);
char				*ft_dup_ws(char *line, int i);
void				set_floor_cell(char *line, t_game *game, char *c, int i);
char				**sp_and_trimm(char *line, t_game *game, char **tab,
						char *c);
int					look_zero(char **tab);
int					color_assignation(t_game *game, char **tab, char *c);
void				set_pos(int i, int j, t_game *game);
int					player_or_sp(char c, t_game *game, int i, int j);
char				*verif_xpm(char *xpm);
int					str_look(char *str, char c);
void				end_map(char **tab, int i);
void				pad_map_lines(char **map);
char				*k_spaces(char *line);
int					max_l(char **tab);

// Nouvelles fonctions utilitaires manquantes
int					ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isdigit(int c);
char				**ft_split(char const *s, char c);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
long				atol(const char *str);
void				print_map(char **map);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strchre(const char *s, int c);

// Fonctions de nettoyage adaptées à ta structure
void				quity(t_game *game, int j, char *str);
void				free_map(t_game *game);
void				free_mlx(t_game *game);
void				free_tab(char **tab);

// Fonctions de gestion des textures
int					load_texture(void *mlx, t_img *texture, char *path);
int					load_all_textures(t_game *game);
int					get_texture_pixel(t_img *texture, int x, int y);
void				cleanup_textures(t_game *game);

// Fonctions bonus (compilées seulement si BONUS_FEATURES=1)
int					mouse_rotation(int x, int y, void *param);
void				init_mouse_events(t_game *game);
void				cleanup_mouse_events(t_game *game);
void				put_pixel(int x, int y, int color, t_game *game);
void				manage_mouse_events(t_game *game, int init);
void				setup_hooks(t_game *game);
int					update_player_bonus(t_game *game);

// Fonctions raycasting bonus
int					ray_casting_bonus(t_game *game);

#endif