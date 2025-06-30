/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:24:39 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/06/30 14:59:20 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ss;
	size_t	i;

	ss = (char *)s;
	i = 0;
	while (i < n)
	{
		ss[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = (NULL);
	p = malloc(nmemb * (size));
	if (p == NULL)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}
