/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:00:34 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/11 12:33:47 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*list;
	t_env	*ptr;
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
		//printf("%d: '%s'  '%s'\n", i, ptr->name, ptr->value);
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
	shell->input = NULL;
	shell->cmdlist = NULL;
	shell->current = NULL;
	shell->heredoc = 0;
	shell->child = 0;
	shell->cmd_nbr = -1;
	return (shell);
}

void	reinit_struct(t_var *shell)
{
	free(shell->input);
	shell->input = NULL;
	shell->cmdlist = NULL;
	shell->current = NULL;
	shell->heredoc = 0;
	shell->child = 0;
	shell->cmd_nbr = -1;
	/*
	if (shell->pids)
		free(shell->pids);
	if (shell->pipe)
		free(shell->pipe);
	*/
}

static int	generate_pipes(t_var *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_nbr - 1)
	{
		if (pipe(shell->pipe + 2 * i) == -1)
			return (1);
		i++;
	}
	return (0);
}

int	init_process(t_var *shell)
{
	shell->cmd_nbr = number_of_cmd(shell);
	shell->pids = malloc(sizeof(int) * shell->cmd_nbr);
	if (!shell->pids)
		return (error_manager(5));
	shell->pipe = malloc(sizeof(int) * 2 * shell->cmd_nbr);
	if (!shell->pipe)
		return (error_manager(6));
	if (generate_pipes(shell))
		return (error_manager(6));
	return (0);
}
