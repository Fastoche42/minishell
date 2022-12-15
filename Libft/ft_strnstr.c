/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:55:45 by mfusil            #+#    #+#             */
/*   Updated: 2022/03/12 19:20:26 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	x;
	size_t	y;

	if (!needle[0])
		return ((char *)haystack);
	x = 0;
	if (haystack || needle)
	{
		while (haystack[x] && x < len)
		{
			y = 0;
			while (haystack[x + y] && needle[y] && x + y < len
				&& haystack[x + y] == needle[y])
				y++;
			if (!needle[y])
				return ((char *)(haystack + x));
			x++;
		}
	}
	return (NULL);
}
