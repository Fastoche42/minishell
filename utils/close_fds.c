/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:36:49 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/24 16:12:31 by event            ###   ########.fr       */
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
	t_cmdlist	*ptr;

	ptr = shell->cmdlist;
	while (ptr)
	{
		if (ptr->fd_in != STDIN_FILENO)
			close(ptr->fd_in);
		if (ptr->fd_out != STDOUT_FILENO)
			close(ptr->fd_out);
		ptr = ptr->next;
	}
}

int	free_strs(char *str, char **strs)
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
			free(strs[i++]);
		free(strs);
		strs = NULL;
	}
	return (1);
}

int	ft_unlink_heredocs(t_var *shell, t_cmdlist *cmd)
{
	int			i;
	t_cmdlist	*ptr;

	i = 0;
	ptr = cmd;
	while (i < shell->cmd_nbr)
	{
		if (ptr->delim_hdoc != NULL)
			if (unlink(ptr->redir_input) == -1)
				return (errno);
		ptr = ptr->next;
		i++;
	}
	return (0);
}
