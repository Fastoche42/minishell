/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:45:50 by mfusil            #+#    #+#             */
/*   Updated: 2022/03/12 11:37:21 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	x;

	x = 0;
	while (src[x] != '\0')
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = src[x];
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*a;

	a = malloc((ft_strlen(s1) + 1) * sizeof(*a));
	if (a == 0)
		return (NULL);
	return (ft_strcpy(a, (char *)s1));
}
