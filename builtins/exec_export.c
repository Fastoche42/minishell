/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:42:01 by fl-hote           #+#    #+#             */
/*   Updated: 2022/12/07 08:03:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_export(char **tmp, t_var *shell)
{
	t_env	*ptr;

	ptr = shell->env;
	while (ptr)
	{
		if (!ft_strcmp(ptr->name, tmp[0]) && ptr->exists == 1)
		{
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}

t_env	*find_export(char **tmp, t_var *shell)
{
	t_env	*ptr;

	ptr = shell->env;
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

int	new_export(char **tmp, t_var *shell)
{
	t_env	*new;

	new = find_export(tmp, shell);
	if (new == NULL)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->name = ft_strdup(tmp[0]);
		new->next = shell->env;
		shell->env = new;
	}
	if (tmp[1])
		new->value = ft_strdup(tmp[1]);
	else
		new->value = ft_strdup(" ");
	if (!new->name || !new->value)
	{
		free (new);
		return (1);
	}
	new->exists = 1;
	new->exported = 1;
	return (0);
}

int	change_export(char **tmp, t_var *shell)
{
	t_env	*new;

	new = find_export(tmp, shell);
	if (!new)
		return (1);
	if (new->value && tmp[1] != NULL)
		free (new->value);
	if (tmp[1] != NULL)
	{
		new->value = ft_strdup(tmp[1]);
		if (!new->value)
		{
			free (new);
			return (1);
		}
	}
	new->exists = 1;
	new->exported = 1;
	return (0);
}

int	exec_export(t_cmdlist *cmd, t_var *shell)
{
	char	**tmp;
	int		i;

	i = 1;
	while (cmd->cmd_arg[i])
	{
		if (ft_strchr(cmd->cmd_arg[i], '=') != NULL)
		{
			tmp = ft_split(cmd->cmd_arg[i], '=');
			if (!tmp)
				return (1);
			if (exec_export2(tmp, shell))
				return (1);
		}
		else if (!check_export(&cmd->cmd_arg[i], shell))
		{
			if (change_export(&cmd->cmd_arg[i], shell))
				return (1);
		}
		i++;
	}
	return (0);
}
