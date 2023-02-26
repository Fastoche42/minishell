/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:46:20 by event             #+#    #+#             */
/*   Updated: 2023/02/21 11:46:22 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_find_newline(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoins(const char *s1, const char *s2)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	s = ft_calloc2(i + j + 1, sizeof(s));
	if (!s)
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
		s[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		s[i + j] = s2[j];
	return (s);
}

char	*ft_strdup2(const char *s1)
{
	char	*s;
	int		i;

	if (!s1)
		return (ft_strdup2(""));
	i = 0;
	while (s1[i])
		i++;
	s = ft_calloc2(i + 1, sizeof(s));
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	return (s);
}

void	*ft_calloc2(size_t nmemb, size_t size)
{
	void			*p;
	unsigned char	*s;
	size_t			t;

	t = nmemb * size;
	p = malloc(t);
	if (!p)
		return (NULL);
	s = (unsigned char *)p;
	while (t != 0)
	{
		*s = '\0';
		s++;
		t--;
	}
	return (p);
}

void	ft_safe_free(char **s, char **s1, char **s2)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 && *s2)
	{
		free(*s2);
		*s2 = NULL;
	}
}
