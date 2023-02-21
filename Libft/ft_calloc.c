/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:31:46 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/21 10:41:09 by event            ###   ########.fr       */
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
