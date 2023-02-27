/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:22:18 by marvin            #+#    #+#             */
/*   Updated: 2023/02/23 16:22:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	jump_to_separ(char *s)
{
	size_t	i;
	char	c;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != ' ' && !ft_isinfsup(s[i]))
	{
		if (ft_isquote(s[i]))
		{
			c = s[i];
			while (s[i + 1] && s[i + 1] != c)
				i++;
		}
		i++;
	}
	return (i);
}

static char	*find_redirfile(char **end)
{
	char	*start;
	char	*str;
	size_t	i;

	start = *end;
	str = NULL;
	if (!*end)
		return (NULL);
	while (**end == ' ')
		(*end)++;
	i = jump_to_separ(*end);
	if (!i)
		return (NULL);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, *end, i + 1);
	*end += i - 1;
	return (str);
}

static void	extract_redir(char **str, char **start, char **end, t_cmdlist *ptr)
{
	ft_concat(str, ft_strndup(*start, (*end - *start)));
	if (**end == '>')
	{
		ptr->flag_append = 0;
		(*end)++;
		if (**end == '>')
		{
			ptr->flag_append = 1;
			(*end)++;
		}
		ptr->redir_output = find_redirfile(end);
		return ;
	}
	(*end)++;
	if (**end == '<')
	{
		(*end)++;
		ptr->delim_hdoc = find_redirfile(end);
		ptr->redir_input = NULL;
		return ;
	}
	ptr->redir_input = find_redirfile(end);
	ptr->delim_hdoc = NULL;
}

void	set_redirs(t_cmdlist *ptr, t_var *sh)
{
	char	*str;
	char	c;

	sh->start = ptr->brut;
	sh->end = sh->start;
	str = NULL;
	while (*(sh->end))
	{
		if (ft_isquote(*(sh->end)))
		{
			c = *(sh->end);
			while (sh->end[1] != c)
				(sh->end)++;
			(sh->end)++;
		}
		else if (ft_isinfsup(*(sh->end)))
		{
			extract_redir(&str, &(sh->start), &(sh->end), ptr);
			sh->start = sh->end + 1;
		}
		(sh->end)++;
	}
	ft_concat(&str, ft_strndup (sh->start, (sh->end - sh->start)));
	free_strs(ptr->brut, NULL);
	ptr->brut = str;
}
