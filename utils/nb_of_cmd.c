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
