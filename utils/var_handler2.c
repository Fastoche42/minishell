#include "../includes/minishell.h"

int	var_handler(t_cmdlist *cmd, t_var *shell)
{
	char	**tmp;
	int		i;

	i = 0;
	while (cmd->cmd_arg[i])
	{
		if (ft_strchr(cmd->cmd_arg[i], '=') != NULL)
		{
			tmp = ft_split(cmd->cmd_arg[i], '=');
			if (!tmp)
				return (1);
			if (var_handler2(tmp, shell))
				return (1);
		}
		i++;
	}
	return (0);
}