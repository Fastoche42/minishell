/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:18:37 by jlorber           #+#    #+#             */
/*   Updated: 2022/06/28 17:14:14 by jlorber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *test_path(char **paths, char *cmd)
{
    char    *cmd_path;
    int		i;
	
	cmd_path = NULL;
    i = 0;
    while (paths[i])
    {
        cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			free_strs(NULL, paths);
			exit_error(msg("Unexpected error", "", "", 1), NULL); // à changer
		}
        if (access(cmd_path, F_OK | X_OK) == 0)
            return(cmd_path);
        free_strs(cmd_path, NULL);
        i++;
    }
    //free_strs(tmp, NULL);
    free_strs(cmd_path, NULL);
    return (NULL);
}

static char **make_paths(char **paths)
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

static char **find_paths(char **envp)
{
    char    *envp_PATH;
    char    **paths;
    int     i;

    i = 0;
    while (envp[i] != NULL && envp[i][0] != '\0')
    {
        envp_PATH = ft_strnstr(envp[i], "PATH=", 5);
        if (envp_PATH)
        {
            envp_PATH = ft_substr(envp_PATH, 5, ft_strlen(envp_PATH));
            if (!envp_PATH)
                return (0);
            break ;
        }
        i++;
    }
    paths = ft_split(envp_PATH, ':');
    free_strs(envp_PATH, NULL);
	if (!paths)
		return (NULL);
	paths = make_paths(paths);
	if (!paths)
		return (NULL);
	return(paths);
}

char *get_cmd(char *cmd, t_var *shell)
{
	char	**env_paths;
	char	*cmd_path;

	if (access(cmd, F_OK | X_OK) == 0)
		return  (ft_strdup(cmd));
	env_paths = find_paths(shell->envp);
	if(!env_paths)
		return (NULL);
	cmd_path = test_path(cmd, env_paths);
	if (!cmd_path)
		msg("Command not found", ": ", shell->cmd_arg[0], 1); // à changer
	free_strs(NULL, env_paths);
	return (cmd_path);
}
