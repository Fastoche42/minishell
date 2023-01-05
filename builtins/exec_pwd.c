/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:12:08 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/07 08:24:10 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_pwd(char **envp)
{
	int		x;

	x = 0;
	while (envp[x])
	{
		if (envp[x][0] == 'P' && envp[x][1] == 'W'
			&& envp[x][2] == 'D' && envp[x][3] == '=')
			{
				printf("%s\n", &envp[x][4]);
				return (0);
			}
		x++;
	}
	return (error_manager(9), ft_putendl_fd("PWD path not found", 2, 1);
}
