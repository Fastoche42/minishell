/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:35:51 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/11 18:55:43 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process(t_var *shell, t_cmdlist *ptr)
{
	pid_t	pid;

	if (pipe(shell->pipe) == -1)
		return (5);
	pid = fork();
	if (pid == -1)
		return (6);
	if (pid == 0) //child
	{
		if (shell->prev_pipe != -1)
			dup2(shell->prev_pipe, STDIN_FILENO);
		if (ptr->next)
			dup2(shell->pipe[1], STDOUT_FILENO);
		close (shell->pipe[0]);
		close (shell->pipe[1]);
		close (shell->prev_pipe);
		which_command(shell);
	}
	else // parent
	{
		close (shell->pipe[1]);
		close (shell->prev_pipe);
		if (ptr->next == NULL)
			close (shell->pipe[0]);
		else
			shell->prev_pipe = shell->pipe[0];
		waitpid(pid, NULL, WUNTRACED);
	}
	return (0);
}

int	number_of_cmd(t_var *shell)
{
	t_cmdlist	*ptr;
	int			cmd_nbr;

	ptr = shell->cmdlist;
	cmd_nbr = 0;
	while (ptr)
	{
		cmd_nbr++;
		ptr = ptr->next;
	}
	return (cmd_nbr);
}

int	ms_execute(t_var *shell)
{
	t_cmdlist	*ptr;
	char		*str;
	char		*path;
	int			cmd_nbr;
	int			i;

	cmd_nbr = number_of_cmd(shell);
	i = 0;
	ptr = shell->cmdlist;
	printf("adresse debut liste %p\n", ptr);
	while (ptr)
	{
		shell->cmd_path = ptr->cmd_path;
		printf("commande %s\n", ptr->cmd_path);
		shell->cmd_arg = ptr->cmd_arg;
		shell->cmd_env = ptr->cmd_env;
		if (ptr->redir_input != NULL | ptr->redir_output != NULL)
			redirection(shell, ptr);
		process(shell, ptr);
		ptr = ptr->next;
		i++;
	}
	dup2(shell->save_input, STDIN_FILENO);
	dup2(shell->save_output, STDOUT_FILENO);
	return (0);
}
