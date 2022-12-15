/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:41:46 by mfusil            #+#    #+#             */
/*   Updated: 2022/03/12 19:24:58 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned long	x;
	unsigned long	y;
	char			*d;
	const char		*s;

	x = 0;
	d = (char *) dst;
	s = (const char *) src;
	if (d || s)
	{
		if (s > d)
			ft_memcpy(dst, src, len);
		else
		{
			y = x;
			x = len;
			while (y++ < len)
			{
				x--;
				d[x] = s[x];
			}
		}
		return (dst);
	}
	return (NULL);
}
