/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:01:27 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/07 08:03:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_true_access(char *cmd, char **path)
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

char	**check_access(t_var *shell, char **var)
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

int	check_path_cmd(t_var *shell, char **var)
{
	shell->cmd_arg = ft_split(shell->input, ' ');
	if (verif_exit(shell->cmd_arg[0]) == 0 || verif_export(shell->cmd_arg[0]) == 0)
		return (0);
	shell->cmd_access = check_access(shell, var);
	shell->cmd_path = check_true_access(shell->cmd_arg[0], shell->cmd_access);
	if (!shell->cmd_path)
		return (2);
	return (0);
}
