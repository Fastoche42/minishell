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

char	*exec_pwd(char **envp)
{
	char	*path_pwd;
	int		x;

	x = 0;
	path_pwd = NULL;
	while (envp[x] && path_pwd == NULL)
	{
		if (envp[x][0] == 'P' && envp[x][1] == 'W'
			&& envp[x][2] == 'D' && envp[x][3] == '=')
			path_pwd = &envp[x][4];
		x++;
	}
	return (path_pwd);
}

// A refaire, lorsque la liste chainee ENV sera prete // ou pas (?)