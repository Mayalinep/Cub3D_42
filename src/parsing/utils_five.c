/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_five.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:35:56 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/09 11:38:21 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*k_spaces(char *line)
{
	int	i;
	int	j;

	if (!line)
		return (NULL);
	i = 0;
	j = ft_strlen(line) - 1;
	while ((line[i] == '\t' || line[i] == ' ') && line[i])
		i++;
	while ((line[j] == '\t' || line[j] == ' ') && j > i)
		j--;
	return (ft_substr(line, i, j - i + 1));
}

int	max_l(char **tab)
{
	int	len;
	int	i;
	int	max_len;

	len = 0;
	max_len = 0;
	i = 0;
	while (tab[i])
	{
		len = ft_strlen(tab[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

int	str_look(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	pad_map_lines(char **map)
{
	int		i;
	size_t	max_len;
	size_t	len;
	char	*new_line;

	max_len = max_l(map);
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < max_len)
		{
			new_line = malloc(max_len + 1);
			if (!new_line)
				return ;
			ft_memcpy(new_line, map[i], len);
			ft_memset(new_line + len, '\0', max_len - len);
			new_line[max_len] = '\0';
			free(map[i]);
			map[i] = new_line;
		}
		i++;
	}
}
