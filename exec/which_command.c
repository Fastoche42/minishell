/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:19:14 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/27 12:46:47 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	which_command(t_var *shell, t_cmdlist *cmd)
{
	if (ft_strcmp (cmd->cmd_arg[0], "pwd") == 0)
		return (exec_pwd(shell->env, cmd));
	else if (ft_strcmp (cmd->cmd_arg[0], "env") == 0)
		return (exec_env(shell->env));
	else if (ft_strcmp (cmd->cmd_arg[0], "echo") == 0)
		return (exec_echo(cmd));
	else if (ft_strcmp (cmd->cmd_arg[0], "exit") == 0)
		exec_exit(cmd, shell);
	else if (ft_strcmp (cmd->cmd_arg[0], "export") == 0)
		return (exec_export(cmd, shell));
	else if (ft_strcmp (cmd->cmd_arg[0], "unset") == 0)
		return (exec_unset(cmd, shell));
	else if (ft_strcmp (cmd->cmd_arg[0], "cd") == 0)
		return (exec_cd(cmd, shell->env));
	else if (ft_strchr(cmd->cmd_arg[0], '='))
		return (var_handler(cmd, shell));
	else
		return (execve(cmd->cmd_path, cmd->cmd_arg, build_envp(shell->env)));
	return (0);
}
