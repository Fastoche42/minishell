/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:52:44 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/07 08:03:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_true_access(char *cmd, char **path)
{
	int		x;
	char	*true_access;
	char	*true_access_cmd;

	x = 0;
	while (path[x])
	{
		true_access = ft_strjoin(path[x], "/");
		true_access_cmd = ft_strjoin(true_access, cmd);
		if (access (true_access_cmd, F_OK | X_OK) == 0)
			return (true_access_cmd);
		x++;
	}
	return (NULL);
}

char	**find_access(t_var *shell, char **var)
{
	int		x;
	char	*path;
	char	**diff_path;

	x = 0;
	path = NULL;
	while (var[x] && path == NULL)
	{
		if (var[x][0] == 'P' && var[x][1] == 'A'
			&& var[x][2] == 'T' && var[x][3] == 'H'
			&& var[x][4] == '=')
			path = &var[x][5];
		x++;
	}
	if (path != NULL)
	{
		diff_path = ft_split(path, ':');
		return (diff_path);
	}
	return (NULL);
}

void	find_cmd(t_var *shell, char **var)
{
	shell->cmd_arg = ft_split(shell->input, ' ');
	shell->cmd_access = find_access(shell, var);
	shell->cmd_path = find_true_access(shell->cmd_arg[0], shell->cmd_access);
}
