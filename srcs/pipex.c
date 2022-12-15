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

static void	redirect_io(int input, int output, t_data *d)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		exit_error(1, d);
	}
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		exit_error(1, d);
	}
}

static void	child(t_cmdlist *cmd)
{
	if (cmd->shell->child == 0)
		redirect_io(cmd->fd_in, cmd->shell->pipe[1], d); //adapter la struct cmdlist (changer redir_input en fd)
	else if (cmd->shell->child == cmd->shell->cmd_nbr - 1)
		redirect_io(cmd->shell->pipe[2 * cmd->shell->child - 2], cmd->fd_out, d); //adapter la struct cmdlist (changer redir_output en fd)
	else
		redirect_io(cmd->shell->pipe[2 * cmd->shell->child - 2], cmd->shell->pipe[2 * cmd->shell->child + 1], d);
	close_fds(cmd->shell);
	if (cmd->cmd_arg == NULL || cmd->cmd_path == NULL)
		exit_error(1, d); // à changer
	if (execve(cmd->cmd_path, cmd->cmd_arg, cmd->shell->envp) == -1)
		exit_error(msg(d->cmd_options[0], ": ", strerror(errno), 1), d); // à changer
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

static int  pipex(t_var *shell)
{
    int exit_code;

    if (pipe(shell->pipe) == -1)
            return(error_manager(6));
    shell->child = 0;
    while (shell->child < shell->cmd_nbr && shell->cmdlist)
    {
        /* d->cmd_options = ft_split(d->argv[d->child + 2 + d->heredoc], ' ');
        if (!d->cmd_options)
                exit_error(msg("unexpected error", "", "", 1), d); */
        shell->cmdlist->cmd_path = get_cmd(shell->cmdlist->cmd_arg[0], shell);
        shell->pids[shell->child] = fork();
        if (shell->pids[shell->child] == -1)
                exit_error(msg("fork", ": ", strerror(errno), 1), d); // à changer
        else if (shell->pids[shell->child] == 0)
                child(shell->cmdlist);
        free_strs(shell->cmd_path, shell->cmd_arg); // à changer
        shell->child++;
		shell->cmdlist = shell->cmdlist->next;
    }
    exit_code = parent(shell);
    if (d->heredoc == 1) // à changer
            unlink(".heredoc.tmp");
    return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	d;
	int		exit_code;

	if (argc < 5)
	{
		if (argc >= 2 && !ft_strcmp("here_doc", argv[1], 9))
                return (msg("Usage: ",
                            "./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2.",
                            "", 1));
        return (msg("Usage: ",
                    "./pipex file1 cmd1 cmd2 ... cmdn file2.", "", 1));
    }
    else if (argc < 6 && !ft_strcmp("here_doc", argv[1], 9))
            return (msg("Usage: ",
                        "./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2.", "", 1));
    if (!envp || envp[0][0] == '\0')
            exit_error(msg("Unexpected error.", "", "", 1), &d);
    d = init(argc, argv, envp);
    exit_code = pipex(&d);
    return (exit_code);
}
