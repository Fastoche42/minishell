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
		if (env_tmp->value)
			free(env_tmp->value);
		free(env_tmp);
	}
	shell->env = NULL;
	cmd_ptr = shell->cmdlist;
	while (cmd_ptr)
	{
		cmd_tmp = cmd_ptr;
		cmd_ptr = cmd_ptr->next;
		if (cmd_tmp->cmd_path)
			free(cmd_tmp->cmd_path);
		if (cmd_tmp->cmd_arg)
			free(cmd_tmp->cmd_arg);
		if (cmd_tmp->redir_input)
			free(cmd_tmp->redir_input);
		if (cmd_tmp->delim_hdoc)
			free(cmd_tmp->delim_hdoc);
		if (cmd_tmp->redir_output)
			free(cmd_tmp->redir_output);
		free(cmd_tmp);
	}
	shell->cmdlist = NULL;
	if (shell->pids)
		free(shell->pids);
	if (shell->pipe)
		free(shell->pipe);
	free(shell);
	shell = NULL;
	return (0);
}

int	exit_minishell(t_var *shell, int exit_code)
{
	if (shell)
		free_all(shell);
	exit(exit_code % 256);
}