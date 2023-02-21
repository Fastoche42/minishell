/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:14:27 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/21 11:44:34 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	x;

	x = 0;
	if (dstsize > 0)
	{
		while (src[x] != '\0' && x + 1 < dstsize)
		{
			dst[x] = (char)src[x];
			x++;
		}
		dst[x] = '\0';
	}
	return (ft_strlen(src));
}
