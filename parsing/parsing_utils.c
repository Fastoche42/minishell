/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:00:58 by marvin            #+#    #+#             */
/*   Updated: 2023/02/20 13:00:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* head = NULL; // utile ?? */
int	free_cmdlist(t_cmdlist **head)
{
	t_cmdlist	*ptr;

	while (*head)
	{
		ptr = *head;
		*head = (*head)->next;
		free_strs(ptr->brut, NULL);
		free_strs(ptr->cmd_path, ptr->cmd_arg);
		free_strs(ptr->redir_input, NULL);
		free_strs(ptr->redir_output, NULL);
		free_strs(ptr->delim_hdoc, NULL);
		free(ptr);
	}
	return (0);
}

t_cmdlist	*new_cmdnode(void)
{
	t_cmdlist	*node;

	node = malloc(sizeof(t_cmdlist));
	if (!node)
		return (NULL);
	node->brut = NULL;
	node->cmd_arg = NULL;
	node->cmd_path = NULL;
	node->cmd_arg = NULL;
	node->redir_input = NULL;
	node->delim_hdoc = NULL;
	node->redir_output = NULL;
	node->flag_append = 0;
	node->fd_in = 0;
	node->fd_out = 1;
	node->next = NULL;
	return (node);
}

char	*what_inside_sq(char **pos)
{
	char	*str;
	int		i;

	i = 0;
	while ((*pos)[i] != '\'')
		i++;
	str = ft_strndup(*pos, i);
	*pos += i;
	return (str);
}

char	*replace_by_var(char **pos, t_env *env)
{
	char	*var;
	int		i;

	i = 1;
	while ((*pos)[i] == '_' || ft_isalnum((*pos)[i]))
		i++;
	var = ft_strndup(*pos, i);
	*pos += (i - 1);
	while (env)
	{
		if (!ft_strcmp(var, env->name))
		{
			free (var);
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	free (var);
	return (NULL);
}

void	ft_concat(char **str, char *str2)
{
	if (!str2)
		return ;
	if (*str)
	{
		*str = ft_realloc(*str, strlen(*str) + strlen(str2) + 1);
		ft_strcat(*str, str2);
		if (str2)
			free (str2);
		str2 = NULL;
	}
	else
		*str = str2;
}
