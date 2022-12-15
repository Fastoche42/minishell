/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:51:38 by mfusil            #+#    #+#             */
/*   Updated: 2022/03/12 11:37:06 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_string(char *i, unsigned int number, int len)
{
	while (number > 0)
	{
		i[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (i);
}

static int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		x;

	len = ft_len(n);
	str = (char *)malloc ((len + 1) * sizeof (char));
	if (!(str))
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		x = n * -1;
		str[0] = '-';
	}
	else
		x = n;
	str = ft_string(str, x, len);
	return (str);
}
