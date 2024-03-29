/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorber <jlorber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:14:34 by jlorber           #+#    #+#             */
/*   Updated: 2023/02/28 18:49:37 by jlorber          ###   ########.fr       */
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
	int		status;
	int		exit_code;

	close_fds(shell);
	close_pipe_fds(shell);
	shell->child--;
	exit_code = 1;
	while (shell->child >= 0)
	{
		g_data.pid = waitpid(shell->pids[shell->child], &status, 0);
		if (g_data.pid == shell->pids[shell->cmd_nbr - 1])
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

	shell->child = 0;
	shell->current = shell->cmdlist;
	while ((shell->child < shell->cmd_nbr) && shell->current)
	{
		if (path_finder(shell))
			return (127);
		if (file_handler(shell->current, shell))
			return (error_manager(12));
		shell->pids[shell->child] = fork();
		if (shell->pids[shell->child] == -1)
			return (error_manager(7));
		else if (shell->pids[shell->child] == 0)
			if (child(shell, shell->current) > 0)
				return (errno);
		shell->child++;
		shell->current = shell->current->next;
	}
	exit_code = parent(shell);
	if (shell->heredoc > 0 && ft_unlink_heredocs(shell, shell->cmdlist) > 0)
		return (error_manager(10));
	return (exit_code);
}

int	one_cmd(t_var *shell)
{
	int	exit_code;

	shell->current = shell->cmdlist;
	close_fds(shell);
	close_pipe_fds(shell);
	if (file_handler(shell->current, shell))
		return (error_manager(12));
	if (shell->current->cmd_arg == NULL
		|| (!is_builtin(shell->current->cmd_arg[0])
			&& shell->current->cmd_path == NULL))
		return (error_manager(10));
	exit_code = which_command(shell, shell->current);
	if (exit_code != 0)
		exit_code = error_manager(10);
	return (exit_code);
}
