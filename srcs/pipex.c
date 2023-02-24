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
	close_pipe_fds(shell); // à verifier
	if (cmd->cmd_arg == NULL || (!is_builtin(cmd->cmd_arg[0]) && cmd->cmd_path == NULL))
		return (error_manager(10));
	if (which_command(shell, cmd) != 0)
		return (error_manager(10));
	close(0);
	close(1);
	exit (0);
}

static int	parent(t_var *shell)
{
	pid_t	wpid;
	int		status;
	int		exit_code;

	close_pipe_fds(shell); // à vérifier
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
	//free(shell->pipe); // a enlever une fois que la fonction pour reinit est faite
	//free(shell->pids); // a enlever une fois que la fonction pour reinit est faite
	return (exit_code);
}

int	pipex(t_var *shell)
{
	int		exit_code;

	shell->child = 0;
	while ((shell->child < shell->cmd_nbr) && shell->cmdlist)
	{
		if (!is_builtin(shell->cmdlist->cmd_arg[0]))
		{
			shell->cmdlist->cmd_path = get_cmd(shell->cmdlist->cmd_arg[0], shell);
			if (!shell->cmdlist->cmd_path)
				return (ft_putendl_fd(ft_strjoin("Command not found: ", shell->cmdlist->cmd_arg[0]), 2 , 1)); // à modifier avec perror */
		}
		if (file_handler(shell->cmdlist)) // gestion des redirections (part 1)
			return (error_manager(12));
		// redirection ici
		// if statement pour forker ou pas
		shell->pids[shell->child] = fork();
		if (shell->pids[shell->child] == -1)
			return (error_manager(7));
		else if (shell->pids[shell->child] == 0)
			if (child(shell, shell->cmdlist) > 0)
				return (errno);
		shell->child++;
		shell->cmdlist = shell->cmdlist->next;
		usleep(100000); // à enlever à la fin
	}
	exit_code = parent(shell);
	if (shell->heredoc > 0)
		if (ft_unlink_heredocs(shell) > 0)
			return (error_manager(10));
	return (exit_code);
}

int	one_cmd(t_var *shell)
{
	int	exit_code;

	close_pipe_fds(shell);
	if (file_handler(shell->cmdlist)) // gestion des redirections (part 1)
		return (error_manager(12));
	if (shell->cmdlist->cmd_arg == NULL || (!is_builtin(shell->cmdlist->cmd_arg[0]) && shell->cmdlist->cmd_path == NULL))
		return (error_manager(10));
	exit_code = which_command(shell, shell->cmdlist);
	if (exit_code != 0)
		exit_code = error_manager(10);
	return (exit_code);
}