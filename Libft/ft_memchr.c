/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:47:56 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/21 11:41:22 by event            ###   ########.fr       */
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
