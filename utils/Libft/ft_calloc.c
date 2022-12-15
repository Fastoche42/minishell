/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:31:46 by mfusil            #+#    #+#             */
/*   Updated: 2022/03/12 19:04:44 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	x;

	x = 0;
	str = malloc(count * size);
	if (!str)
		return (NULL);
	while (x < count * size)
	{
		str[x] = 0;
		x++;
	}
	return (str);
}
