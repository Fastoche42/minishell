/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:44:09 by event             #+#    #+#             */
/*   Updated: 2023/02/20 11:31:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *src, size_t n)
{
    size_t len;
    char *dest;
    len = ft_strlen(src);
    if (n < len)
      len = n;
    dest = malloc(len + 1);
    if (!dest)
      return (NULL);
    dest[len] = '\0';
    return ((char *) ft_memcpy(dest, src, len));
}