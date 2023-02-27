/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:19:01 by event             #+#    #+#             */
/*   Updated: 2023/02/27 11:01:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_w(char *str)
{
	int		i;
	int		is_word;
	char	car;

	i = 0;
	is_word = 0;
	while (str && *str)
	{
		if (ft_isquote(*str))
		{
			if (!is_word)
			{
				is_word = 1;
				i++;
			}
			car = *str;
			str++;
			while (str[0] != car)
				str++;
		}
		else if ((*str == ' ') == is_word)
		{
			is_word = 1 - is_word;
			if (is_word)
				i++;
		}
		str++;
	}
	return (i);
}

static size_t	jump_to_blank(char *s)
{
	size_t	i;
	char	c;

	i = 0;
	while (s[i] && s[i] != ' ')
	{
		if (ft_isquote(s[i]))
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
		{
				i++;
		}
		}
		i++;
	}
	return (i);
}

char	**split_token(char *s)
{
	char	**tab;
	size_t	i_word;
	size_t	i;

	if (!s)
		return (NULL);
	tab = ft_calloc((count_w(s) + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	i_word = 0;
	while (*s)
	{
		if (*s == ' ')
			s++;
		else
		{
			i = jump_to_blank(s);
			tab[i_word] = malloc(sizeof(char) * (i + 1));
			if (!tab[i_word])
				return (NULL);
			ft_strlcpy(tab[i_word++], s, i + 1);
			s += i;
		}
	}
	return (tab);
}
