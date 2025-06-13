/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:50:46 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/13 15:22:41 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdio.h>
# include <limits.h> 
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./GNL/get_next_line.h"
# ifndef MAX_MAP_LINES
# define MAX_MAP_LINES 100
# endif

typedef struct s_game
{
    char	**map;
	char	*file;
    char	*NO;
    char	*SO;
    char	*WE;
    char	*EA;
    char	*F;
    char	*C;
    int     dir;
    
}   t_game;

// verifications
int	look_one(char *line, t_game *game);
int verif(int ac, char **av, t_game *game);
void init_game(t_game *game);
void	verif_bis(t_game *game);
int	look_side(char **map, int i, int j, t_game *game);



//utils
int	ft_strlen(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_isdigit(int c);
void print_map(char **map);
char	*ft_strdup(const char *s);
void	quity(t_game *game, int j);


//mapping
void get_map(int file, t_game *game);
int	add_line(t_game *game, char *line, int i);
char	*ft_dup_ws(char *line, int i);







#endif