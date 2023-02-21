/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:09:18 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/21 11:45:08 by event            ###   ########.fr       */
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
