/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:55:56 by fl-hote           #+#    #+#             */
/*   Updated: 2023/01/19 16:56:10 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	heredoc_file_generator(t_cmdlist *cmd, t_var *shell)
{
	char *tmp;

	tmp = ft_itoa(shell->heredoc);
	if (!tmp)
		return (error_manager(11));
	if (cmd->redir_input)
		free(cmd->redir_input);
	cmd->redir_input = ft_strjoin(".heredoc.tmp", tmp);
	free (tmp);
	if (!cmd->redir_input)
		return (error_manager(11));
	shell->heredoc++;
	return (0);
}

static int	get_heredoc(t_cmdlist *cmd, t_var *shell)
{
	int		tmp_fd;
	int		stdin_fd;
	char	*line;

	if (heredoc_file_generator(cmd, shell))
		return (1);
	tmp_fd = open(cmd->redir_input, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	stdin_fd = dup(STDIN_FILENO);
	if (tmp_fd == -1)
		return (1);
	line = "";
	while (1)
	{
		ft_putstr_fd("> ", 1, 0);
		line = get_next_line(stdin_fd);
		if (line == NULL) // à tester
			break ;
		if (ft_strlen(cmd->delim_hdoc) + 1 == ft_strlen(line)
			&& !ft_strncmp(line, cmd->delim_hdoc, ft_strlen(cmd->delim_hdoc + 1)))
			close(stdin_fd);
		else
			ft_putstr_fd(line, tmp_fd, 0);
		free(line);
	}
	close(tmp_fd);
	return (0);
}

static int	get_input_file(t_cmdlist *cmd, t_var *shell)
{
	if (cmd->delim_hdoc)
	{
		if (get_heredoc(cmd, shell))
			return (1);
		cmd->fd_in = open(cmd->redir_input, O_RDONLY);
		if (cmd->fd_in == -1)
			return (1);
	}
	else if (cmd->redir_input)
	{
		cmd->fd_in = open(cmd->redir_input, O_RDONLY, 0644);
		if (cmd->fd_in == -1)
			return (1);
	}
	return (0);
}

static int	get_output_file(t_cmdlist *cmd)
{
	if (cmd->flag_append)
		cmd->fd_out = open(cmd->redir_output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cmd->redir_output)
		cmd->fd_out = open(cmd->redir_output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out == -1)
		return (1);
	return (0);
}

int	file_handler(t_cmdlist *cmd, t_var *shell)
{
	if (get_input_file(cmd, shell) || get_output_file(cmd))
		return (1);
	return (0);
}
