#include "../includes/minishell.h"

int	free_all(t_var *shell) //esquisse de fonction pour free tout proprement (en fin d'execution ou en cas de "exit")
{
	t_env	*env_ptr;
	t_env	*env_tmp;
	t_cmdlist	*cmd_ptr;
	t_cmdlist	*cmd_tmp;

	env_ptr = shell->env;
	while (env_ptr)
	{
		env_tmp = env_ptr;
		env_ptr = env_ptr->next;
		free(env_tmp->name);
		env_tmp->name = NULL;
		if (env_tmp->value)
		{
			free(env_tmp->value);
			env_tmp->value = NULL;
		}
		free(env_tmp);
	}
	shell->env = NULL;
	cmd_ptr = shell->cmdlist;
	while (cmd_ptr)
	{
		cmd_tmp = cmd_ptr;
		cmd_ptr = cmd_ptr->next;
		if (cmd_tmp->cmd_path != NULL)
		{
			free(cmd_tmp->cmd_path);
			cmd_tmp->cmd_path = NULL;
		}
		if (cmd_tmp->cmd_arg != NULL)
		{
			free(cmd_tmp->cmd_arg);
			cmd_tmp->cmd_arg = NULL;
		}
		if (cmd_tmp->redir_input != NULL)
		{
			free(cmd_tmp->redir_input);
			cmd_tmp->redir_input = NULL;
		}
		if (cmd_tmp->delim_hdoc != NULL)
		{
			free(cmd_tmp->delim_hdoc);
			cmd_tmp->delim_hdoc = NULL;
		}
		if (cmd_tmp->redir_output != NULL)
		{
			free(cmd_tmp->redir_output);
			cmd_tmp->redir_output = NULL;
		}
		free(cmd_tmp);
	}
	shell->cmdlist = NULL;
	shell = NULL;
	return (0);
}

int	exit_minishell(t_var *shell, int exit_code)
{
	if (shell != NULL)
		free_all(shell);
	exit(exit_code % 256);
}