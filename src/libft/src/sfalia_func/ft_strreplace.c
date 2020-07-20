#include "libft.h"

char *ft_strreplace(char const *str, char *orig, char *sub)
{
    char    *rez[3];
    int     len[2];

    if (!str || !orig || !sub)
        return (NULL);
    rez[0] = (char *)str;
    len[0] = ft_strlen(orig);
    len[1] = ft_strlen(sub);
    rez[2] = 0;
    while ((rez[0] = ft_strstr(rez[0], orig)))
    {
        rez[2]++;
        rez[0] += len[0];
    }
    rez[0] = ft_strnew(ft_strlen(str) + (len[1] - len[0]) * (int)rez[2]);
    rez[1] = rez[0];
    while (*str)
    {
        rez[2] = ft_strstr(str, orig);
        ft_strncpy(rez[0], str, rez[2] - str);
        rez[0] += rez[2] - str;
        ft_strncpy(rez[0], sub, rez[2] ? len[1] : 0);
        str += rez[2] - str + (!rez[2] ? 0 : len[0]);
    }
    return (rez[1]);
}

char *ft_strreplacefirst(char const *str, char *orig, char *sub)
{
    char    *rez[3];
    int     len[2];

    if (!str || !orig || !sub)
        return (NULL);
    rez[0] = (char *)str;
    len[0] = ft_strlen(orig);
    len[1] = ft_strlen(sub);
    rez[2] = 0;
    while ((rez[0] = ft_strstr(rez[0], orig)))
    {
        rez[2]++;
        rez[0] += len[0];
    }
    rez[0] = ft_strnew(ft_strlen(str) + (len[1] - len[0]) * (int)rez[2]);
    rez[1] = rez[0];
    rez[2] = ft_strstr(str, orig);
    ft_strncpy(rez[0], str, rez[2] - str);
    rez[0] += rez[2] - str;
    ft_strncpy(rez[0], sub, rez[2] ? len[1] : 0);
    str += rez[2] - str + (!rez[2] ? 0 : len[0]);
    return (rez[1]);
}
