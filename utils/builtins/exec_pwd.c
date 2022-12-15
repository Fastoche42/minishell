/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:12:08 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/07 08:24:10 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*exec_pwd(t_var *shell, char **var)
{
	char	*path_pwd;
	int		x;

	x = 0;
	path_pwd = NULL;
	while (var[x] && path_pwd == NULL)
	{
		if (var[x][0] == 'P' && var[x][1] == 'W'
			&& var[x][2] == 'D' && var[x][3] == '=')
			path_pwd = &var[x][4];
		x++;
	}
	return (path_pwd);
}

// A refaire, lorsque la liste chainee ENV sera prete