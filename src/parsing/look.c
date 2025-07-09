/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:27:15 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/09 11:39:42 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	look_sprites(t_game *game)
{
	if (!game->parsed_data.texture_south)
		return (-1);
	if (!game->parsed_data.texture_east)
		return (-1);
	if (!game->parsed_data.texture_west)
		return (-1);
	if (!game->parsed_data.texture_north)
		return (-1);
	if (game->parsed_data.ceiling_b < 0 || game->parsed_data.ceiling_b > 255
		|| game->parsed_data.ceiling_r < 0 || game->parsed_data.ceiling_r > 255
		|| game->parsed_data.ceiling_g < 0 || game->parsed_data.ceiling_g > 255)
		return (-1);
	if (game->parsed_data.floor_b < 0 || game->parsed_data.floor_b > 255
		|| game->parsed_data.floor_g < 0 || game->parsed_data.floor_g > 255
		|| game->parsed_data.floor_r < 0 || game->parsed_data.floor_r > 255)
		return (-1);
	return (0);
}

void	end_map(char **tab, int i)
{
	if (i == 0)
		return ;
	while (tab[--i] && tab[i][0] == '\n')
	{
		free(tab[i]);
		tab[i] = NULL;
	}
}

char	*verif_xpm(char *xpm)
{
	int		i;
	int		fd;
	char	*str;

	str = ft_strdup(xpm + 2);
	i = ft_strlen(xpm) - 1;
	fd = -1;
	while (xpm[i] == '\t' || xpm[i] == ' ')
		i--;
	if (xpm[i--] != 'm')
		return (free(xpm), NULL);
	if (xpm[i--] != 'p')
		return (free(xpm), NULL);
	if (xpm[i--] != 'x')
		return (free(xpm), NULL);
	if (xpm[i--] != '.')
		return (free(xpm), NULL);
	fd = open(xpm, O_RDONLY);
	if (fd == -1)
		return (free(xpm), NULL);
	close(fd);
	free(xpm);
	return (str);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dd;
	char	*ss;
	size_t	i;

	ss = (char *)src;
	dd = (char *)dest;
	i = 0;
	if (!ss && !dd)
		return (NULL);
	while (i < n)
	{
		dd[i] = ss[i];
		i++;
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ss;

	ss = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ss[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
