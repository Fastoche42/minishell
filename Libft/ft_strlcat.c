/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:56:28 by mfusil            #+#    #+#             */
/*   Updated: 2022/03/12 11:37:25 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < dstsize && dst[x])
		x++;
	y = x;
	if (dstsize > 0)
	{
		while (src[x - y] && x < dstsize - 1)
		{
			dst[x] = src[x - y];
			x++;
		}
		if (y < dstsize)
			dst[x] = '\0';
	}
	return (ft_strlen(src) + y);
}
