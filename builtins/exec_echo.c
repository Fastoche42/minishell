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

int	exec_echo(t_cmdlist *cmd)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (ft_strcmp(cmd->cmd_arg[i], "-n") == 0)
	{
		flag = 1;
		i = i + 1;
	}
	fprintf(stderr, "flag = %d\n", flag);
	fprintf(stderr, "i = %d\n", i);
	while (cmd->cmd_arg[i] != NULL)
	{
		fprintf(stderr, "IM IN THE WHILE LOOP\n");
		printf("%s", cmd->cmd_arg[2]);
		printf(" ");
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
