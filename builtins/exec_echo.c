/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:08:34 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/07 08:03:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_echo(t_cmdlist *cmd)
{
	int		i;

	i = 0;
	while (cmd->cmd_arg[1][i])
	{
		if (cmd->cmd_arg[1][i] == '\"')
		{
			//ft_putchar_fd('"', cmd->redir_output); // à adapter pour le bon FD de sortie
			ft_putchar_fd('"', 1); 
		}
		else 
		{
			//ft_putchar_fd(cmd->cmd_arg[1][i], cmd->redir_output); // à adapter pour le bon FD de sortie
			ft_putchar_fd(cmd->cmd_arg[1][i], 1); 
		}
		i++;
	}
	if (ft_strcmp(cmd->cmd_arg[2], "-n") != 0)
		printf("\n");
}
