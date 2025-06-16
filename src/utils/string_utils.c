#include "../../include/cub3d.h"

// Duplique une chaîne de caractères
char *ft_strdup(const char *s)
{
    char *dup;
    int len;
    int i;
    
    if (!s)
        return (NULL);
    
    len = 0;
    while (s[len])
        len++;
    
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    
    i = 0;
    while (i <= len)
    {
        dup[i] = s[i];
        i++;
    }
    
    return (dup);
} 