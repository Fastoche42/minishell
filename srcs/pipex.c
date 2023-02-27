/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:14:34 by jlorber           #+#    #+#             */
/*   Updated: 2023/02/05 00:35:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_io(int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		return (1);
	}
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		return (1);
	}
	if (input != STDIN_FILENO)
		close(input);
	if (output != STDOUT_FILENO)
		close(output);
	return (0);
}

static int	child(t_var *shell, t_cmdlist *cmd)
{
	if ((shell->child == 0) || (shell->child == shell->cmd_nbr - 1))
	{
		redir_first_last(shell, cmd);
	}
	else
	{
		redir_other(shell, cmd);
	}
	close_fds(shell);
	close_pipe_fds(shell);
	if (cmd->cmd_arg == NULL
		|| (!is_builtin(cmd->cmd_arg[0])
		&& cmd->cmd_path == NULL))
		return (error_manager(10));
	if (which_command(shell, cmd) != 0)
		return (error_manager(10));
	exit (0);
}

static int	parent(t_var *shell)
{
	pid_t	wpid;
	int		status;
	int		exit_code;

	close_fds(shell);
	close_pipe_fds(shell);
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
	return (exit_code);
}

int	pipex(t_var *shell)
{
	int			exit_code;
	t_cmdlist	*tmp;

	shell->child = 0;
	tmp = shell->cmdlist;
	while ((shell->child < shell->cmd_nbr) && shell->cmdlist)
	{
		if (path_finder(shell))
			return (127);
		if (file_handler(shell->cmdlist, shell))
			return (error_manager(12));
		shell->pids[shell->child] = fork();
		if (shell->pids[shell->child] == -1)
			return (error_manager(7));
		else if (shell->pids[shell->child] == 0)
			if (child(shell, shell->cmdlist) > 0)
				return (errno);
		shell->child++;
		shell->cmdlist = shell->cmdlist->next;
	}
	exit_code = parent(shell);
	if (shell->heredoc > 0 && ft_unlink_heredocs(shell, tmp) > 0)
		return (error_manager(10));
	return (exit_code);
}

int	one_cmd(t_var *shell)
{
	int	exit_code;

	close_fds(shell);
	close_pipe_fds(shell);
	if (file_handler(shell->cmdlist, shell))
		return (error_manager(12));
	if (shell->cmdlist->cmd_arg == NULL
		|| (!is_builtin(shell->cmdlist->cmd_arg[0])
		&& shell->cmdlist->cmd_path == NULL))
		return (error_manager(10));
	exit_code = which_command(shell, shell->cmdlist);
	if (exit_code != 0)
		exit_code = error_manager(10);
	return (exit_code);
}