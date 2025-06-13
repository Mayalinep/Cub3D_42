/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:14:24 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/13 18:15:47 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int verif(int ac, char **av, t_game *game)
{
	int i;
	int	file;

	i = ft_strlen(av[1]);
	if (ac!= 2)
		return (-1);
	if((av[1][--i])!= 'b')
		return(-1);
	if((av[1][--i])!= 'u')
		return(-1);
	if((av[1][--i])!= 'c')
		return(-1);
	if((av[1][--i])!= '.')
		return(-1);
	file = open(av[1], R_OK);
	if (file == -1)
		return(printf("er01\n"), -1);
	get_map(file, game);
	return (0);
}

void get_map(int file, t_game *game)
{
	int i;
	int flag;
	int flags;
	char *line;
	
	i = 0;
	flag = 1;
	while(flag)
	{
		flags = 1;
		line = get_next_line(file);
		if (!line)
			break;
		if (*line == '\n')
		{
			flags = 0;
			free(line);	
		}
		if(line && flags == 1)
		{
			if (look_one(line, game) != 0 )
			{
				flag = add_line(game, line, i);
				i++;
			}
		}
	}
	game->map[i] = NULL;
	verif_bis(game);
}

void	verif_bis(t_game *game)
{
	int i;
	int j;
	if (!game->SO || !game->EA || !game->WE || !game->NO || !game->F ||  !game->C)
		exit(1);
	i = 0;
	j = 0;
	while (game->map[j])
	{
		while (game->map[j][i])
		{
			if (game->map[j][i] == '0' && look_side(game->map, i, j, game) == 1)
					quity(game, 2);
			if (game->map[j][i] == 'S' || game->map[j][i] == 'E' || game->map[j][i] == 'N' || game->map[j][i] == 'W')
					game->dir++;
			i++;
		}
		i = 0;
		j++;
	}	
}

int	look_side(char **map, int i, int j, t_game *game)
{
	//printf("ligne %i indice %i\n", j, i);
	if (!map || !map[j] || i < 1 || j < 1)
		return (-1);

	if (map[j + 1] == NULL || map[j - 1] == NULL)
		printf("1jsp a ligne %s et ligne %i index %i\n", map[j], j, i), quity(game, 2);
	if ((int)ft_strlen(map[j]) <= i + 1 || i <= 0)
		printf("2jsp a ligne %s et ligne %i index %i\n", map[j], j, i), quity(game, 2);
	if (map[j - 1][i] && map[j + 1][i] != '0' && map[j + 1][i] != '1' && map[j + 1][i] != 'N')
		printf("3jsp a ligne %s et ligne %i index %i\n", map[j+ 1], j, i), quity(game, 2);
	if (map[j - 1][i] && map[j - 1][i] != '1' && map[j - 1][i] != '0' && map[j - 1][i] != 'N')
		printf("4jsp a ligne %s et ligne %i index %i\n", map[j], j, i), quity(game, 2);
	if (map[j][i + 1] && map[j][i + 1] != '1' && map[j][i + 1] != '0' && map[j][i + 1] != 'N')
		printf("5jsp a ligne %c et ligne %i index %i\n", map[j][i + 1], j, i), quity(game, 2);
	if (map[j][i - 1] && map[j][i - 1] != '1' && map[j][i - 1] != '0' && map[j][i - 1] != 'N')
		printf("6jsp a ligne %s et ligne %i index %i\n", map[j], j, i), quity(game, 2);
	return (0);
}


int look_sprites(t_game *game)
{
	if (!game->SO)
		return (-1);
	if (!game->EA)
		return (-1);
	if (!game->WE)
		return (-1);
	if (!game->NO)
		return (-1);
	if (!game->F)
		return (-1);
	if (!game->C)
		return (-1);
	return (0);
}

int	add_line(t_game *game, char *line, int i)
{
	//printf("%i\n\n\n\n", i);
	if (!line || *line == '\n')
		exit(1);
	game->map[i] = ft_strdup(line);
	if (!game->map[i])
		exit(0);
	free(line);
	//free(game->map[i]);
	return (1);
}

int	look_one(char *line, t_game *game)
{
	if (!line)
		return (-1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return(game->SO = ft_dup_ws(line, 2), 0);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return(game->NO = ft_dup_ws(line, 2), 0);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (game->WE = ft_dup_ws(line, 2), 0);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return(game->EA = ft_dup_ws(line, 2), 0);
	if (ft_strncmp(line, "F ", 2) == 0)
		return(game->F = ft_dup_ws(line, 1), 0);
	if (ft_strncmp(line, "C ", 2) == 0)
		return(game->C = ft_dup_ws(line, 1), 0);
	return (1);
}

char	*ft_dup_ws(char *line, int i)
{
	char *str;
	
	while(line[i] != '.' && line[i] && ft_isdigit(line[i]) == 0)
		i++;
	str = ft_strdup(line + i);
	free(line);
	return(str);
}

void init_game(t_game *game)
{
	game->C = NULL;
	game->SO = NULL;
	game->F = NULL;
	game->NO = NULL;
	game->WE = NULL;
	game->EA = NULL;
	game->file = NULL;
	game->map = malloc(sizeof(char *) * MAX_MAP_LINES);
	if (!game->map)
    	exit(1);
}
