/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:37:51 by mfusil            #+#    #+#             */
/*   Updated: 2022/03/12 19:12:16 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dst, const void *src, size_t n)
{
	unsigned long	x;
	char			*d;
	const char		*s;

	x = 0;
	d = (char *) dst;
	s = (const char *) src;
	if (d || s)
	{
		while (x < n)
		{
			d[x] = s[x];
			x++;
		}
		return (dst);
	}
	return (NULL);
}
