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
	if (shell->cmdlist->fd_in != -1)
		close(shell->cmdlist->fd_in);
	if (shell->cmdlist->fd_out != -1)
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
