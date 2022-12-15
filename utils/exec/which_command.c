/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:19:14 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/09 11:30:10 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	which_command(t_var *shell)
{
	if (ft_strcmp (shell->input, "pwd") == 0)
		printf("%s\n", exec_pwd(shell, shell->cmd_env));
	else if (ft_strcmp (shell->input, "env") == 0)
		exec_env(shell, shell->cmd_env);
	else if (ft_strcmp (first_arg(shell), "echo") == 0)
		exec_echo(shell);
	else if (ft_strcmp (first_arg(shell), "exit") == 0)
		exec_exit(shell);
	else if (ft_strcmp (first_arg(shell), "export") == 0)
		exec_export(shell, shell->cmd_env);
	else if (ft_strcmp (first_arg(shell), "cd") == 0)
		exec_cd(shell);
	else
		execve(shell->cmd_path, shell->cmd_arg, shell->cmd_env);
	exit (0);
}
