/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:36:29 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/01 17:36:35 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_first_last(t_var *shell, t_cmdlist *cmd)
{
	if (shell->child == 0)
	{
		if (cmd->redir_output != NULL || shell->cmd_nbr == 1)
		{
			if (redirect_io(cmd->fd_in, cmd->fd_out))
				return (error_manager(11));
		}
		else if (shell->cmd_nbr > 1)
		{	
			if (redirect_io(cmd->fd_in, shell->pipe[1]))
				return (error_manager(11));
		}
	}
	else if (shell->child == shell->cmd_nbr - 1 && shell->cmd_nbr > 1)
	{
		if (cmd->redir_input)
		{
			if (redirect_io(cmd->fd_in, cmd->fd_out))
				return (error_manager(11));
		}
		else
		{
			if (redirect_io(shell->pipe[2 * shell->child - 2], cmd->fd_out))
				return (error_manager(11));
		}
	}
	return (0);
}

int	redir_other(t_var *shell, t_cmdlist *cmd)
{
	if (cmd->redir_input && cmd->redir_output)
	{
		if (redirect_io(cmd->fd_in, cmd->fd_out))
			return (error_manager(11));
	}
	else if (cmd->redir_output)
	{
		if (redirect_io(shell->pipe[2 * shell->child - 2], cmd->fd_out))
			return (error_manager(11));
	}
	else if (cmd->redir_input)
	{
		if (redirect_io(cmd->fd_in, shell->pipe[2 * shell->child + 1]))
			return (error_manager(11));
	}
	else
	{
		if (redirect_io(shell->pipe[2 * shell->child - 2], shell->pipe[2 * shell->child + 1]))
			return (error_manager(11));
	}
	return (0);
}
