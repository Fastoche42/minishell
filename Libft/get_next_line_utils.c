#include "get_next_line.h"

int     ft_find_newline(const char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

void    ft_safe_free(char **s, char **s1, char **s2)
{
    if (s && *s)
    {
        free(*s);
        *s = NULL;
    }
    if (s1 && *s1)
    {
        free(*s1);
        *s1 = NULL;
    }
    if (s2 && *s2)
    {
        free(*s2);
        *s2 = NULL;
    }
}