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
/*
int	exit_number_of_args(t_var *shell)
{
	char	**tab;
	int		i;
	int		args;

	i = 1;
	args = 0;
	tab = ft_split(shell->input, ' ');
	while (tab[i])
	{
		args++;
		i++;
	}
	return (args);
}

int	exec_exit(t_var *shell)
{
	int	args;
	int	exit_status;

	args = exit_number_of_args(shell);
	exit_status = 0;
	if (args > 0)
		return (write (1, "too many arguments\n", 19));
	else
	{
		write(1, "exit\n", 1);
		exit(exit_status);
		return (0);
	}
}
*/

int	exec_exit(t_cmdlist *cmd)
{
	int	i;

	i = -1;
	if (cmd->cmd_arg[1] != NULL)
	{
		while (cmd->cmd_arg[1][++i])
		{
			if (!ft_isdigit(cmd->cmd_arg[1][i]))
			{
				ft_putstr_fd("exit\n", 1, 0);
				ft_putstr_fd("minishell: exit: ", 1, 0);
				ft_putstr_fd(cmd->cmd_arg[1], 1, 0);
				ft_putstr_fd(": numeric argument required\n", 1, 0);
				exit (255);
			}
		}
		if (cmd->cmd_arg[2])
		{
			ft_putstr_fd("exit\n", 1, 0);
			ft_putstr_fd("minishell: exit: too many arguments\n", 1, 0);
		}
		else
		{
			ft_putstr_fd("exit\n", 1, 0);
			exit (ft_atoi(cmd->cmd_arg[1]));
		}
	}
	else
		exit (g_exit_code);
	return (0); // à vérifier
}