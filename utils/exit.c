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
		free_strs(env_tmp->name, NULL);
		free_strs(env_tmp->value, NULL);
		free(env_tmp);
	}
	shell->env = NULL;
	cmd_ptr = shell->cmdlist;
	while (cmd_ptr)
	{
		cmd_tmp = cmd_ptr;
		cmd_ptr = cmd_ptr->next;
		free_strs(cmd_tmp->brut, NULL);
		free_strs(cmd_tmp->cmd_path, cmd_tmp->cmd_arg);
		free_strs(cmd_tmp->redir_input, NULL);
		free_strs(cmd_tmp->redir_output, NULL);
		free_strs(cmd_tmp->delim_hdoc, NULL);
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