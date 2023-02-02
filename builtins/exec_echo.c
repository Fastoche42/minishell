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

// modifiée car inutile de préciser le fd de sortie, la sortie standard aura déjà été redirigée vers le bon fd
/*void	exec_echo(t_cmdlist *cmd)
{
	int		i;

	i = 0;
	while (cmd->cmd_arg[1][i])
	{
		if (cmd->cmd_arg[1][i] == '\"')
		{
			ft_putchar_fd('\"', cmd->fd_out);
		}
		else
		{
			ft_putchar_fd(cmd->cmd_arg[1][i], cmd->fd_out);
		}
		i++;
	}
	if (ft_strcmp(cmd->cmd_arg[2], "-n") != 0)
		printf("\n");
}*/

int	exec_echo(t_cmdlist *cmd) // nouvelle version corrigée
{
	if (cmd->cmd_arg[1])
		printf("%s", cmd->cmd_arg[1]);
	if (ft_strcmp(cmd->cmd_arg[2], "-n") != 0)
		printf("\n");
	return (0);
}
