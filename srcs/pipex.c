/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:14:34 by jlorber           #+#    #+#             */
/*   Updated: 2022/07/04 17:33:21 by jlorber          ###   ########.fr       */
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

static int	child(t_cmdlist *cmd)
{
	if (cmd->shell->child == 0)
	{
		if (redirect_io(cmd->fd_in, cmd->shell->pipe[1], cmd)) //adapter la struct cmdlist (changer redir_input en fd)
			return (error_manager(11));
	}
	else if (cmd->shell->child == cmd->shell->cmd_nbr - 1)
	{
		if (redirect_io(cmd->shell->pipe[2 * cmd->shell->child - 2], cmd->fd_out, cmd)) //adapter la struct cmdlist (changer redir_output en fd)
			return (error_manager(11));
	}
	else
	{
		if (redirect_io(cmd->shell->pipe[2 * cmd->shell->child - 2], cmd->shell->pipe[2 * cmd->shell->child + 1], cmd))
			return (error_manager(11));
	}
	close_fds(cmd->shell); // à adapter
	if (cmd->cmd_arg == NULL || cmd->cmd_path == NULL)
		return (error_manager(10));
	if (execve(cmd->cmd_path, cmd->cmd_arg, cmd->shell->envp) == -1)
		return (error_manager(10));
	return (0);
}

static int	parent(t_var *shell)
{
	pid_t	wpid;
	int		status;
	int		exit_code;

	close_fds(shell);
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

int  pipex(t_var *shell)
{
    int exit_code;

    if (pipe(shell->pipe) == -1)
            return(error_manager(6));
    shell->child = 0;
    while (shell->child < shell->cmd_nbr && shell->cmdlist)
    {
        shell->cmdlist->cmd_path = get_cmd(shell->cmdlist->cmd_arg[0], shell);
		if (!shell->cmdlist->cmd_path)
		{
			return (ft_putendl_fd(ft_strjoin("Command not found: ", shell->cmdlist->cmd_arg[0]), 2 , 1));
		}
        shell->pids[shell->child] = fork();
        if (shell->pids[shell->child] == -1)
                return (error_manager(7));
        else if (shell->pids[shell->child] == 0)
                if (child(shell->cmdlist) > 0)
					return (1);
        // free_strs(shell->cmd_path, shell->cmd_arg); // à changer
        shell->child++;
		shell->cmdlist = shell->cmdlist->next;
    }
    exit_code = parent(shell);
    if (shell->heredoc > 0)
            ft_unlink_fds(shell); // à écrire
    return (exit_code);
}
