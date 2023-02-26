/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:08:34 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/24 13:23:24 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_echo(t_cmdlist *cmd)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (cmd->cmd_arg[i] && ft_strcmp(cmd->cmd_arg[i], "-n") == 0)
	{
		flag = 1;
		i++;
	}
	while (cmd->cmd_arg[i] != NULL)
	{
		ft_putstr_fd(cmd->cmd_arg[i], 1, 0);
		i++;
		if (cmd->cmd_arg[i] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
