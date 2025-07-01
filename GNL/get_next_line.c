/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:54:47 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/24 13:39:52 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substrg( char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strleng(s))
		return (ft_strdupg(""));
	if (len > (unsigned int)ft_strleng(s + start))
		len = ft_strleng(s + start);
	str = ft_callocg(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}

char	*fill_strg(int fd, char *line, char *buffer)
{
	ssize_t	ret;
	char	*temp;

	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			free(line);
			return (NULL);
		}
		else if (ret == 0)
			break ;
		buffer[ret] = 0;
		if (!line)
			line = ft_strdupg("");
		temp = line;
		line = ft_strjoing(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line);
}

static char	*set_line(char *line)
{
	char	*stock;
	ssize_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == 0 || line[1] == 0)
		return (NULL);
	stock = ft_substrg(line, i + 1, ft_strleng(line) - i);
	if (*stock == 0)
	{
		free(stock);
		stock = NULL;
	}
	line[i + 1] = '\0';
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(res);
		free(buffer);
		res = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_strg(fd, res, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	res = set_line(line);
	return (line);
}
