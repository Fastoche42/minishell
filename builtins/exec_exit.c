/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:50:58 by fl-hote           #+#    #+#             */
/*   Updated: 2022/12/07 08:03:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_exit(t_cmdlist *cmd, t_var *shell)
{
	int	i;

	i = -1;
	if (cmd->cmd_arg[1] != NULL)
	{
		while (cmd->cmd_arg[1][++i])
		{
			if (!ft_isdigit(cmd->cmd_arg[1][i]))
			{
				ft_putstr_fd("\nminishell: exit: ", 1, 0);
				ft_putstr_fd(cmd->cmd_arg[1], 1, 0);
				ft_putstr_fd(": numeric argument required\n", 1, 0);
				exit_minishell(shell, 255);
			}
		}
		if (cmd->cmd_arg[2])
			ft_putstr_fd("\nminishell: exit: too many arguments\n", 1, 0);
		else
			exit_minishell(shell, ft_atoi(cmd->cmd_arg[1]));
	}
	else
		exit_minishell(shell, g_data.exit_code);
	return (0);
}
