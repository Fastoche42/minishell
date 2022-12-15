/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:50:18 by mfusil            #+#    #+#             */
/*   Updated: 2022/03/12 11:37:17 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	x;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		x = -n;
	}
	else
		x = n;
	if (x > 9)
	{
		ft_putnbr_fd(x / 10, fd);
		x %= 10;
	}
	ft_putchar_fd(x + '0', fd);
}
