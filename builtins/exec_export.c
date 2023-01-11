/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:42:01 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/07 08:03:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
char	**exec_export_2(t_var *shell, char **var, char **tmp)
{
	char	**tab;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 1;
	tab = ft_split(shell->input, ' ');
	str = modif_input(tab[j]);
	while (var[i])
	{
		tmp[i] = var[i];
		i++;
	}
	tmp[i] = ft_strdup(str);
	return (tmp);
}

int	exec_export(t_var *shell, char **var)
{
	char	**tmp;
	int		i;

	i = 0;
	if (check_export(shell->input))
		return (error_manager(4));
	tmp = malloc((ft_nb_lines_tab(var) + 1) * sizeof(char *));
	tmp = exec_export_2(shell, var, tmp);
	free(var);
	var = malloc((ft_nb_lines_tab(tmp)) * sizeof(char *));
	while (tmp[i])
	{
		var[i] = tmp[i];
		i++;
	}
	free(tmp);
	return (0);
} */

static int	check_export(char **tmp, t_env *env)
{
	t_env 	*ptr;

	ptr = env;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, tmp[0]))
		{
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

static t_env	*find_export(char **tmp, t_env *env)
{
	t_env 	*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strcmp(ptr->name, tmp[0]))
		{
			return (ptr);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

static int	new_export(char **tmp, t_env *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->name = ft_strdup(tmp[0]);
	if (tmp[1])
		new->value = ft_strdup(tmp[1]);
	else 
		new->value = ' ';
	new->exists = 1;
	new->exported = 1;
	new->next = env;
	env = new;
	return (0);
}

static int	change_export(char **tmp, t_env *env)
{
	t_env	*new;

	new = find_export(tmp, env);
	if (!new)
		return (1);
	free (new->value);
	new->value = ft_strdup(tmp[1]);
	new->exists = 1;
	new->exported = 1;
	return (0);
}

int	exec_export(t_cmdlist *cmd, t_env *env)
{
	t_env 	*new;
	char	**tmp;
	int		i;

	i = 1;
	while (cmd->cmd_arg[i])
	{
		if (ft_strchr(cmd->cmd_arg[i], '=') != NULL) // double check
		{
			tmp = ft_split(cmd->cmd_arg[i], '='); // vérifier ft_split
			if (!tmp)
				return (1);
			if (check_export(tmp, env))
				if (change_export(tmp, env))
					return (1);
			else if (new_export(tmp, env))
				return (1);		
			free (tmp);
		}
		i++;
	}
	return (0);
}