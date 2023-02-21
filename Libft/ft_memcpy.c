/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:37:51 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/21 11:41:37 by event            ###   ########.fr       */
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
