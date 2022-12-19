/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:11:18 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/08 15:58:13 by fl-hote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	child_process(t_var *shell)
{
	pid_t	pid;

	if (pipe(shell->pipe) == -1)
		return (5); // code d'erreur pipe a pas marche
	pid = fork();
	if (pid == -1)
		return (6); // code d'erreur fork qui a fail
	if (pid == 0) // processus enfant
	{
		close (shell->pipe[0]);
		dup2(shell->pipe[1], STDOUT_FILENO);
		which_command(shell, shell->cmdlist);
	}
	else // processus pere
	{
		close (shell->pipe[1]);
		dup2(shell->pipe[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	open_file(char *str, int i)
{
	int	file;

	if (i == 0)
		file = open(str, O_RDONLY, 777);
	if (i == 1)
		file = open(str, O_WRONLY | O_CREAT | O_TRUNC, 777);
	return (file);
}

int	new_pipex(t_var *shell)
{
	int	i;
	int	j;

	i = 1;
	j = ft_strlen_char(shell->cmd_arg);
	if (j >= 4)
	{	
		// shell->fd_input = open_file(shell->cmd_arg[0], 0);
		// shell->fd_output = open_file(shell->cmd_arg[j - 1], 1);
		//dup2(shell->fd_input, STDIN_FILENO);
		while (i < j - 2)
		{
			child_process(shell);
			i++;
		}
		dup2(shell->fd_output, STDOUT_FILENO);
	}
	return (7); //int d'erreur pour dire pas assez d'arguments pour executer pipex
}

/**il me faudrait un split de l'input sur chaque mot (sauf les commandes ou j'ai besoin des options avec)**/