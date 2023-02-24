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
		else if (*end == '>')
		{
			if (ptr->redir_output) // multi non géré
				return (error_manager(21));
			if (end > start)
				ft_concat(&str, ft_strndup (start, (end - start)));
			end++;
			if (*end == '>')
				ptr->flag_append = 1;
			//ptr->redir_output = find_redirfile(&end);
		}
		end++;
	}
	return (0);
}
