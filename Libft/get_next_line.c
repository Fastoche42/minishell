/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:46:10 by event             #+#    #+#             */
/*   Updated: 2023/02/21 11:46:14 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static char	*ft_before_newline(const char *tmp)
{
	char	*ret;
	int		i;

	i = 0;
	while (tmp[i] != '\0' && tmp[i] != '\n')
		i++;
	if (tmp[i] != '\0' && tmp[i] == '\n')
		i++;
	ret = ft_calloc(i + 1, sizeof(ret));
	if (!ret)
		return (NULL);
	i = 0;
	while (tmp[i] != '\0' && tmp[i] != '\n')
	{
		ret[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
	{
		ret[i] = tmp[i];
		i++;
	}
	return (ret);
}

static char	*ft_after_newline(const char *tmp)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tmp && tmp[j])
		j++;
	while (tmp[i] != '\0' && tmp[i] != '\n')
		i++;
	if (tmp[i] != '\0' && tmp[i] == '\n')
		i++;
	ret = ft_calloc((j - i) + 1, sizeof(ret));
	if (!ret)
		return (NULL);
	j = 0;
	while (tmp[i + j])
		{
			ret[j] = tmp[i + j];
			j++;
		}
	return (ret);
}

static void	ft_read_line(int fd, char **keep, char **tmp)
{
	char	*buffer;
	int		ret;

	//buffer = malloc(sizeof(buffer) * (BUFFER_SIZE + 1));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1)); // a valider
	if (!buffer)
		return ;
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			ft_safe_free(&buffer, keep, tmp);
			return ;
		}
		buffer[ret] = '\0';
		*tmp = ft_strdup(*keep);
		ft_safe_free(keep, 0, 0);
		*keep = ft_strjoin(*tmp, buffer);
		ft_safe_free(tmp, 0, 0);
		if (ft_find_newline(*keep))
			break ;
	}
	ft_safe_free(&buffer, 0, 0);
}

static char	*ft_parse_line(char **keep, char **tmp)
{
	char	*line;

	*tmp = ft_strdup(*keep);
	ft_safe_free(keep, 0, 0);
	*keep = ft_after_newline(*tmp);
	line = ft_before_newline(*tmp);
	ft_safe_free(tmp, 0 , 0);
	return (line);
}

char	*get_next_line(int fd)
{
	static char *keep = NULL;
	char		*tmp;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	next_line = NULL;
	tmp = NULL;
	ft_read_line(fd, &keep, &tmp);
	if (keep != NULL && *keep != '\0')
		next_line = ft_parse_line(&keep, &tmp);
	if (!next_line || *next_line == '\0')
	{
		ft_safe_free(&keep, &next_line, &tmp);
		return (NULL);
	}
	return (next_line);
}
