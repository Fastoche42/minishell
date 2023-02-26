/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinfsup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 21:45:37 by marvin            #+#    #+#             */
/*   Updated: 2023/02/25 21:45:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isinfsup(int c)
{
	int	x;

	x = 0;
	if (c == '<' || c == '>')
	{
		x = 1;
	}
	return (x);
}
