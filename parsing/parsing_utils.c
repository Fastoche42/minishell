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

void	skip_car(char **pos, char c)
{
	if (**pos != c)
		return ;
	if (c == ' ')
	{
		while (**pos == ' ')
			(*pos)++;
	}
	else // quotes
	{
		while ((*(*pos)+1) != c)
			(*pos)++;
	}
}

int	free_cmdlist(t_cmdlist **head)
{
	t_cmdlist	*ptr;

	while (*head)
	{
		ptr = *head;
		*head = (*head)->next;
		free(ptr->brut);
		//free_strs(NULL, ptr->cmd_arg);
		free(ptr->cmd_path);
		free(ptr->redir_input);
		free(ptr->redir_output);
		free(ptr->delim_hdoc);
		free(ptr);
	}
	//head = NULL; // utile ??
	return (0);
}

t_cmdlist	*new_cmdnode(void)
{
	t_cmdlist	*node;

	node = malloc(sizeof(t_cmdlist));
	if (!node)
		return (NULL);
	node->brut = NULL;
	node->cmd_path = NULL;
	node->redir_input = NULL;
	node->delim_hdoc = NULL;
	node->redir_output = NULL;
	node->flag_append = 0;
	node->fd_in = 0;
	node->fd_out = 1;
	node->next = NULL;
	return (node);
}

char	*replace_by_var(char **pos, t_env *env)
{
	char	*var;
	int		i;

	i = 1; //le 1e car est deja testé
	while ((*pos)[i] == '_' || ft_isalnum((*pos)[i]))
		i++;
	var = ft_strndup(*pos, i);
	*pos += (i - 1);
	printf("<%c> ", **pos);
	while (env)
	{
		if (!ft_strcmp(var, env->name))
		{
			free (var);
			return (env->value);
		}
		env = env->next;
	}
	free (var);
	return (NULL);
}

void    ft_concat(char **str, char *str2)
{
	if(!str2)
		return ;
	if(*str)
	{
		*str = ft_realloc(*str, strlen(*str) + strlen(str2) + 1);
		ft_strcat(*str, str2);
		free (str2);
	}
	else
		*str = str2;
}
