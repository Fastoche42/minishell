/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:41:46 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/21 11:41:44 by event            ###   ########.fr       */
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
