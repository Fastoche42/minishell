/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscarvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 21:45:37 by marvin            #+#    #+#             */
/*   Updated: 2023/02/25 21:45:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iscarvar(int c)
{
	int	x;

	x = 0;
	if (c == '?' || c == '_' || ft_isalpha(c))
	{
		x = 1;
	}
	return (x);
}