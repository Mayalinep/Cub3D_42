/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:54:40 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/01/11 00:19:42 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include "get_next_line.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strdupg( char *s);
int		ft_strleng(char *str);
char	*ft_substrg( char *s, unsigned int start, size_t len);
char	*ft_strjoing( char *s1, char *s2);
char	*fill_strg(int fd, char *line, char *buffer);
void	*ft_callocg(size_t nmemb, size_t size);
// static char	*ft_strchr(char *s, int c);

#endif