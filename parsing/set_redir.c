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
	i = jump_to_blank(*end);
	if (!i)
		return (NULL);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, *end, i + 1);
	*end += i;
	return (str);
}

int set_redirs(t_cmdlist *ptr)
{
	char	*start;
	char	*end;
	char	*str;
	char	*str2;

	start = ptr->brut;
	end = start;
	str = NULL;
	while (*end)
	{
		if (*end == '\'')
		{
			while (end[1] != '\'')
				end++;
			end++;
		}
		else if (*end == '"')
		{
			while (end[1] != '"')
				end++;
			end++;
		}
		else if (*end == '>') // si pluieurs on prend le dernier sans erreur
		{
			if (end > start)
				ft_concat(&str, ft_strndup (start, (end - start)));
			end++;
			ptr->flag_append = 0;
			if (*end == '>')
			{
				ptr->flag_append = 1;
				end++;
			}
			ptr->redir_output = find_redirfile(&end);
			start = end + 1;
		}
		else if (*end == '<') // si pluieurs on prend le dernier sans erreur
		{

			ptr->delim_hdoc = find_redirfile(&end);
			ptr->redir_input = find_redirfile(&end);
			start = end + 1;
		}
		end++;
	}
	if (end > start)
		ft_concat(&str, ft_strndup (start, (end - start)));
	free (ptr->brut);
	ptr->brut = str;
	return (0);
}
