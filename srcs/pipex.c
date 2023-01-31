/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:14:34 by jlorber           #+#    #+#             */
/*   Updated: 2023/01/23 16:27:44 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	redirect_io(int input, int output, t_cmdlist *cmd)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		return (1);
	}
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		return (1);
	}
	return (0);
}

static int	child(t_var *shell, t_cmdlist *cmd)
{
	if ((shell->child == 0) || (shell->child == shell->cmd_nbr - 1))
		redir_first_last(shell, cmd);
	else
		redir_other(shell, cmd);
	close_fds(shell); // à verifier
	if (cmd->cmd_arg == NULL || cmd->cmd_path == NULL)
		return (error_manager(10));
	if (which_command(shell, cmd) != 0)
		return (error_manager(10));
	return (0);
}

static int	parent(t_var *shell)
{
	pid_t	wpid;
	int		status;
	int		exit_code;

	close_fds(shell); // à vérifier
	shell->child--;
	exit_code = 1;
	while (shell->child >= 0)
	{
		wpid = waitpid(shell->pids[shell->child], &status, 0);
		if (wpid == shell->pids[shell->cmd_nbr - 1])
		{
			if ((shell->child == (shell->cmd_nbr - 1)) && WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		shell->child--;
	}
	free(shell->pipe);
	free(shell->pids);
	return (exit_code);
}

int	pipex(t_var *shell)
{
	int		exit_code;
	t_var	*ptr;

	ptr = shell;
	if (shell->cmd_nbr > 1) // à vérifier
		if (pipe(shell->pipe) == -1)
			return (error_manager(6));
	shell->child = 0;
	while (shell->child < shell->cmd_nbr && ptr->cmdlist) // boucle à modifier par Jojo (done)
	{
		ptr->cmdlist->cmd_path = get_cmd(ptr->cmdlist->cmd_arg[0], shell);
		if (!ptr->cmdlist->cmd_path)
			return (ft_putendl_fd(ft_strjoin("Command not found: ", ptr->cmdlist->cmd_arg[0]), 2 , 1)); // à modifier avec perror 
		if (file_handler(ptr->cmdlist)) // gestion des redirections (part 1)
			return (error_manager(12));
		shell->pids[shell->child] = fork();
		if (shell->pids[shell->child] == -1)
			return (error_manager(7));
		else if (shell->pids[shell->child] == 0)
			if (child(shell, ptr->cmdlist) > 0)
				return (errno);
		free_strs(ptr->cmdlist->cmd_path, ptr->cmdlist->cmd_arg); // à vérifier // à adapter
		shell->child++;
		ptr->cmdlist = ptr->cmdlist->next;
	}
	exit_code = parent(shell);
	if (shell->heredoc > 0)
		if (ft_unlink_heredocs(shell) > 0)
			return (error_manager(10));
	return (exit_code);
}
