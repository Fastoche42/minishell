#include "../includes/minishell.h"

int	redir_first_last(t_var *shell, t_cmdlist *cmd)
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
	return (0);
}

int	redir_other(t_var *shell, t_cmdlist *cmd)
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
	return (0);
}