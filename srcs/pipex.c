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

static int	child(t_var *shell, t_cmdlist *cmd) // il faut "un peu" raccourcir
{
	if (shell->child == 0)
	{
		if (cmd->redir_output || !shell->pipe)
			if (redirect_io(cmd->fd_in, cmd->fd_out, cmd))
				return (error_manager(11));
		else
			if (redirect_io(cmd->fd_in, shell->pipe[1], cmd))
				return (error_manager(11));
	}
	else if (shell->child == shell->cmd_nbr - 1)
	{
		if (cmd->redir_input)
			if (redirect_io(cmd->fd_in, cmd->fd_out, cmd))
				return (error_manager(11));
		else
			if (redirect_io(shell->pipe[2 * shell->child - 2], cmd->fd_out, cmd))
				return (error_manager(11));
	}
	else
	{
		if (cmd->redir_input && cmd->redir_output)
			if (redirect_io(cmd->fd_in, cmd->fd_out, cmd))
				return (error_manager(11));
		else if (cmd->redir_output)
			if (redirect_io(shell->pipe[2 * shell->child - 2], cmd->fd_out, cmd))
				return (error_manager(11));
		else if (cmd->redir_input)
			if (redirect_io(cmd->fd_in, shell->pipe[2 * shell->child + 1], cmd))
				return (error_manager(11));
		else
			if (redirect_io(shell->pipe[2 * shell->child - 2], shell->pipe[2 * shell->child + 1], cmd))
				return (error_manager(11));
	}
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
			return (ft_putendl_fd(ft_strjoin("Command not found: ", ptr->cmdlist->cmd_arg[0]), 2 , 1));
		if (file_handler(ptr->cmdlist)) // gestion des redirections
			return (error_manager(12));
		shell->pids[shell->child] = fork();
		if (shell->pids[shell->child] == -1)
			return (error_manager(7));
		else if (shell->pids[shell->child] == 0)
			if (child(shell, ptr->cmdlist) > 0) // param doit etre la copie du ptr (done)
				return (1);
		free_strs(ptr->cmdlist->cmd_path, ptr->cmdlist->cmd_arg); // à vérifier // à adapter
		shell->child++;
		ptr->cmdlist = ptr->cmdlist->next; //à changer pour une copie de ptr (done)
	}
	exit_code = parent(shell);
	if (shell->heredoc > 0)
		//ft_unlink_heredocs(shell); // à écrire
		return (0); // temp
	return (exit_code);
}
