#include "../includes/minishell.h"

static int	check_var(char **tmp, t_env *env)
{
	t_env 	*ptr;

	ptr = env;
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

static t_env	*find_var(char **tmp, t_env *env)
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

static int	new_var(char **tmp, t_env *env)
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
	new->next = env;
	env = new;
	return (0);
}

static int	change_var(char **tmp, t_env *env)
{
	t_env	*new;

	new = find_var(tmp, env);
	if (!new)
		return (1);
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

int	var_handler(t_cmdlist *cmd, t_env *env)
{
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
			if (!check_export(tmp, env))
			{
				if (change_export(tmp, env))
				{
					free (tmp);
					return (1);
				}
			}
			else if (new_export(tmp, env))
			{
				free (tmp);
				return (1);
			}	
			free (tmp);
		}
		i++;
	}
	return (0);
}