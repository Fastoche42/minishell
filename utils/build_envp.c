#include "../includes/minishell.h"

static int	env_lstlen(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	env = tmp;
	return (i);
}

static char	*env_strjoin(char *name, char *value)
{
	char *ret;
	int	i;
	int	j;

	i = 0;
	j = 0;
	ret = (char *)malloc(ft_strlen(name) + ft_strlen(value) + 1);
	while (name[i])
	{
		ret[j] = name[i];
		j++;
		i++;
	}
	ret[j++] = '=';
	i = 0;
	while (value[i])
	{
		ret[j] = value[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

char	**build_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		i;

	tmp = env;
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
	env = tmp;
	return (envp);
}
