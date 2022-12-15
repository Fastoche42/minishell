/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:00:34 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/11 12:33:47 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*list;
	t_env	*ptr;
	t_env	*new;
	int		i;
	int		c;

	i = 0;
	while (envp[i])
	{
		if (i == 0)
		{
			list = malloc (sizeof(t_env));
			ptr = list;
		}
		else
		{
			ptr->next = malloc (sizeof(t_env));
			ptr = ptr->next;
		}
		if (!ptr)
			return (NULL);
		c = ft_strposchr(envp[i], '='); // 1e '=' en partant de la gauche
		ptr->name = ft_substr(envp[i], 0, c);
		ptr->value = ft_substr(envp[i], c + 1, strlen(envp[i]) - c);
		ptr->exists = 1;
		ptr->exported = 1;
		ptr->next = NULL;
		printf("%d: '%s'  '%s'\n", i, ptr->name, ptr->value);
		i++;
	}
	return (list);
}

t_var	*init_struct(char **envp)
{
	t_var	*shell;

	shell = malloc(sizeof(t_var));
	if (!shell)
		return (NULL);
	shell->env = init_env(envp);
	if (!shell->env)
	{
		free(shell);
		return (NULL);
	}
	shell->cmd_access = NULL;
	shell->cmd_path = NULL;
	shell->cmd_arg = NULL;
	shell->cmd_env = NULL;
	shell->redir_input = NULL;
	shell->redir_hdoc = NULL;
	shell->redir_output = NULL;
	shell->redir_append = NULL;
	shell->fd_input = 0;
	shell->fd_output = 0;
	shell->outfile = 0;
	shell->infile = 0;
	shell->prev_pipe = -1;
	shell->save_input = dup(STDIN_FILENO);
	shell->save_output = dup(STDOUT_FILENO);
	return (shell);
}
