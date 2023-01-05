/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:47:59 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/07 08:03:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cd(t_cmdlist *cmd)
{
	
	if (chdir(cmd->cmd_arg[1]) != 0)
		return (error_manager(9), ft_putendl_fd(strerror(errno), 2, 1));
	if (update_pwd(cmd))
		return (1);
	return (0);
}

int	update_pwd(t_cmdlist *cmd) //à parfaire
{
	int	i;
	char *tmp;

	i = 0;
	while (cmd->shell->envp[i])
	{
		if (cmd->shell->envp[i][0] == 'P' && cmd->shell->envp[i][1] == 'W'
			&& cmd->shell->envp[i][2] == 'D' && cmd->shell->envp[i][3] == '=')
			{
				tmp = cmd->shell->envp[i][4];
				cmd->shell->envp[i][4] = cmd->cmd_arg[1];
				if (!tmp || !cmd->shell->envp[i][4])
					return (1);
			}
		if (cmd->shell->envp[i][0] == 'O' && cmd->shell->envp[i][1] == 'L'
			&& cmd->shell->envp[i][2] == 'D' && cmd->shell->envp[i][3] == 'P'
			&& cmd->shell->envp[i][4] == 'W' && cmd->shell->envp[i][5] == 'D')
				cmd->shell->envp[i][7] = tmp;
	}
	return (0);
}