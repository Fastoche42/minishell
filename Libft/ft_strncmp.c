/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:09:18 by mfusil            #+#    #+#             */
/*   Updated: 2022/03/12 11:37:31 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	n = n - 1;
	while (*s1 == *s2 && *s1 && n)
	{
		s1++;
		s2++;
		--n;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
