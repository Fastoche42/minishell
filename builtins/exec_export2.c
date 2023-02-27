#include "../includes/minishell.h"

int	exec_export2(char **tmp, t_var *shell)
{
	if (!check_export(tmp, shell))
	{
		if (change_export(tmp, shell))
		{
			free_strs(NULL, tmp);
			return (1);
		}
	}
	else if (new_export(tmp, shell))
	{
		free_strs(NULL, tmp);
		return (1);
	}
	free_strs(NULL, tmp);
	return (0);
}