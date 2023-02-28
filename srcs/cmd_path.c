/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:18:37 by jlorber           #+#    #+#             */
/*   Updated: 2023/01/19 17:01:12 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*test_path(char *cmd, char **paths)
{
	char	*cmd_path;
	int		i;

	cmd_path = NULL;
	i = 0;
	while (paths[i] != NULL)
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			free_strs(NULL, paths);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_strs(cmd_path, NULL);
		i++;
	}
	return (NULL);
}

static char	**make_paths(char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		free_strs(tmp, NULL);
		i++;
	}
	return (paths);
}

static char	**find_paths(char **envp)
{
	char	*envp_path;
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] != NULL && envp[i][0] != '\0')
	{
		envp_path = ft_strnstr(envp[i], "PATH=", 5);
		if (envp_path)
		{
			envp_path = ft_substr(envp_path, 5, ft_strlen(envp_path));
			if (!envp_path)
				return (0);
			break ;
		}
		i++;
	}
	paths = ft_split(envp_path, ':');
	free_strs(envp_path, NULL);
	if (!paths)
		return (NULL);
	paths = make_paths(paths);
	if (!paths)
		return (NULL);
	return (paths);
}

char	*get_cmd(char *cmd, t_var *shell)
{
	char	**env_paths;
	char	*cmd_path;
	char	**envp;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	envp = build_envp(shell->env);
	if (!envp)
		return (NULL);
	env_paths = find_paths(envp);
	free_strs(NULL, envp);
	if (!env_paths)
		return (NULL);
	cmd_path = test_path(cmd, env_paths);
	free_strs(NULL, env_paths);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

int	path_finder(t_var *shell)
{
	if (!is_builtin(shell->current->cmd_arg[0]))
	{
		shell->current->cmd_path = get_cmd(shell->current->cmd_arg[0], shell);
		if (!shell->current->cmd_path)
		{
			ft_putstr_fd("Command not found: ", 2, 1);
			ft_putendl_fd(shell->current->cmd_arg[0], 2, 1);
			return (1);
		}
	}
	return (0);
}
