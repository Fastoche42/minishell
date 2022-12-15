/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:47:56 by mfusil            #+#    #+#             */
/*   Updated: 2022/03/12 11:37:07 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			x;
	char			*str;

	x = 0;
	str = (char *) s;
	while (x < n)
	{
		if (str[x] == c)
			return ((void *) str + x);
		x++;
	}
	return (NULL);
}
