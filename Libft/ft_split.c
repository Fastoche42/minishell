/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:21:41 by mfusil            #+#    #+#             */
/*   Updated: 2022/03/14 14:53:07 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrs_word(char const *s1, char c)
{
	size_t	x;
	size_t	word;

	x = 0;
	word = 0;
	while (s1[x] == c)
		x++;
	while (s1[x])
	{
		if (s1[x] == c)
		{
			word++;
			while (s1[x] == c)
			x++;
		}
		else
			x++;
	}
	word++;
	return (word);
}

static char	*ft_subword(char const *str, int start, int finish)
{
	char	*word;
	int		x;

	x = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[x++] = str[start++];
	word[x] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab_str;
	size_t	x;
	size_t	y;
	int		index;

	if (!s)
		return (NULL);
	x = -1;
	y = 0;
	index = -1;
	tab_str = malloc(sizeof(char *) * (ft_nbrs_word(s, c) + 1));
	if (!(tab_str))
		return (NULL);
	while (++x <= ft_strlen(s))
	{
		if (s[x] != c && index < 0)
			index = x;
		else if ((s[x] == c || x == ft_strlen(s)) && index >= 0)
		{
			tab_str[y++] = ft_subword(s, index, x);
			index = -1;
		}
	}
	tab_str[y] = NULL;
	return (tab_str);
}
