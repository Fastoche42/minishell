/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:19:14 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/09 11:30:10 by fl-hote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	which_command(t_var *shell, t_cmdlist *cmd)
{
	if (ft_strcmp (cmd->cmd_arg[0], "pwd") == 0)
		printf("%s\n", exec_pwd(shell->envp));
	else if (ft_strcmp (cmd->cmd_arg[0], "env") == 0)
		exec_env(shell->envp);
	else if (ft_strcmp (cmd->cmd_arg[0], "echo") == 0)
		exec_echo(cmd);
	else if (ft_strcmp (cmd->cmd_arg[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp (cmd->cmd_arg[0], "export") == 0)
		exec_export(shell, shell->envp);
	else if (ft_strcmp (cmd->cmd_arg[0], "unset") == 0)
		exec_unset(cmd, shell->envp);
	else if (ft_strcmp (cmd->cmd_arg[0], "cd") == 0)
		exec_cd(cmd);
	else
		execve(cmd->cmd_path, cmd->cmd_arg, shell->envp);
}
