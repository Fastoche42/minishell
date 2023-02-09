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

static void	close_pipe_fds(t_var *shell)
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
	printf("&shell:%p cmdlist:%p\n", shell, shell->cmdlist);
	printf("fdin:%d, fdout:%d\n", shell->cmdlist->fd_in, shell->cmdlist->fd_out);
	//if (shell->cmdlist->fd_in != -1)
	if (shell->cmdlist->fd_in > 2)
		close(shell->cmdlist->fd_in);
	//if (shell->cmdlist->fd_out != -1)
	if (shell->cmdlist->fd_out > 2)
		close(shell->cmdlist->fd_out);
	close_pipe_fds(shell);
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
			if(unlink(shell->cmdlist[i].redir_input) == -1)
				return (errno);
		i++;
	}
	return (0);
}
