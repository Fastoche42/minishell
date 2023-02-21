/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:36:49 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/07 16:02:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipe_fds(t_var *shell)
{
	int	i;

	i = 0;
	while (i < (shell->cmd_nbr - 1) * 2)
	{
		close(shell->pipe[i]);
		i++;
	}
}

void	close_fds(t_var *shell)
{
	if (shell->cmdlist)
	{
		if (shell->cmdlist->fd_in > 2)
			close(shell->cmdlist->fd_in);
		if (shell->cmdlist->fd_out > 2)
			close(shell->cmdlist->fd_out);
	}
	if (shell->child == 0)
		close(shell->pipe[1]);
	else if (shell->child == shell->cmd_nbr - 1)
		close(shell->pipe[2 * shell->child - 2]);
	else
	{
		close(shell->pipe[shell->child * 2 - 2]);
		close(shell->pipe[shell->child * 2 + 1]);
	}
	//close_pipe_fds(shell);
}

void	free_strs(char *str, char **strs)
{
	int	i;

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (strs != NULL)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}

int	ft_unlink_heredocs(t_var *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_nbr)
	{
		if (shell->cmdlist[i].delim_hdoc != NULL)
			if (unlink(shell->cmdlist[i].redir_input) == -1)
				return (errno);
		i++;
	}
	return (0);
}
