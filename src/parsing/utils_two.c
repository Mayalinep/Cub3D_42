/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:22:39 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/07/08 12:52:53 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rep;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > (unsigned int)ft_strlen(s + start))
		len = (unsigned int)ft_strlen(s + start);
	rep = ft_calloc(len + 1, sizeof(char));
	if (!rep)
		return (NULL);
	while (i < len)
	{
		rep[i] = s[i + start];
		i++;
	}
	return (rep);
}

static int	count_words(char const *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
		if (str[i] == '\0')
			break ;
		else
			i++;
	}
	return (count);
}

static void	free_words(char **tab, int count)
{
	while (count >= 0)
	{
		free(tab[count]);
		count--;
	}
	free(tab);
}

static char	**ft_fill_words(char const *s, char c, char **tab, int i)
{
	int	j;
	int	k;

	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i + j] && s[i + j] != c)
				j++;
			tab[k] = ft_substr(s, i, j);
			if (tab[k] == NULL)
			{
				free_words(tab, k - 1);
				return (NULL);
			}
			k++;
			i += j;
		}
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**tab;

	if (!s)
		return (NULL);
	len = count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	tab = ft_fill_words(s, c, tab, 0);
	if (!tab)
		return (NULL);
	return (tab);
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
