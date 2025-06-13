/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:59:05 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/13 17:52:16 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned const char)s1[i] - (unsigned const char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void print_map(char **map)
{
    int i;
	i = 0;
    while (map[i])
    {
        printf("%s", map[i]);
        i++;
    }
	printf("\n");
	//free(map);
}

char	*ft_strdup(const char *s)
{
	char	*c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[j])
		j++;
	c = malloc(j * sizeof(const char) + 1);
	if (c == NULL)
		return (NULL);
	while (s[i])
	{
		c[i] = s[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}
void	quity(t_game *game, int j)
{
	int i;
	
	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	if(game->C)
		free(game->C);
	if(game->SO)
		free(game->SO);
	if(game->EA)
		free(game->EA);
	if(game->WE)
		free(game->WE);
	if(game->NO)
		free(game->NO);
	if(game->F)
		free(game->F);
	free(game);
	exit(j);
}
