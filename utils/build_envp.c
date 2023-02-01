/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:31:28 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/01 17:41:04 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	number_of_cmd(t_var *shell)
{
	t_cmdlist	*ptr;
	int			cmd_nbr;

	ptr = shell->cmdlist;
	cmd_nbr = 0;
	while (ptr)
	{
		cmd_nbr++;
		ptr = ptr->next;
	}
	return (cmd_nbr);
}

static int	env_lstlen(t_env *env)
{
	int		i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static char	*env_strjoin(char *name, char *value)
{
	char *ret;
	int	i;
	int	j;

	i = 0;
	j = 0;
	ret = (char *)malloc(ft_strlen(name) + ft_strlen(value) + 2);
	while (name[i])
		ret[j++] = name[i++];
	ret[j++] = '=';
	i = 0;
	while (value[i])
		ret[j++] = value[i++];
	ret[j] = '\0';
	return (ret);
}

char	**build_envp(t_env *env)
{
	char	**envp;
	int		i;

	i = 0;
	envp = malloc(sizeof(char *) * (env_lstlen(env) + 1));
	while (env)
	{
		if (env->exists && env->exported)
		{
			envp[i] = env_strjoin(env->name, env->value);
			if (!envp[i])
				return (NULL);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
