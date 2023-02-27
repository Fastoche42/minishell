/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:33:30 by jlorber           #+#    #+#             */
/*   Updated: 2023/02/27 14:33:32 by jlorber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_var(char **tmp, t_var *shell)
{
	t_env	*ptr;

	ptr = shell->env;
	while (ptr)
	{
		if (!ft_strcmp(ptr->name, tmp[0]))
		{
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}

static t_env	*find_var(char **tmp, t_var *shell)
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

static int	new_var(char **tmp, t_var *shell)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->name = ft_strdup(tmp[0]);
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
	new->exported = 0;
	new->next = shell->env;
	shell->env = new;
	return (0);
}

static int	change_var(char **tmp, t_var *shell)
{
	t_env	*new;

	new = find_var(tmp, shell);
	if (!new)
		return (1);
	if (new->value)
		free (new->value);
	new->value = ft_strdup(tmp[1]);
	if (!new->value)
	{
		free (new);
		return (1);
	}
	new->exists = 1;
	return (0);
}

int	var_handler2(char **tmp, t_var *shell)
{
	if (!check_var(tmp, shell))
	{
		if (change_var(tmp, shell))
		{
			free (tmp);
			return (1);
		}
	}
	else if (new_var(tmp, shell))
	{
		free (tmp);
		return (1);
	}
	free (tmp);
	return (0);
}
