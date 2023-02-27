#include "../includes/minishell.h"

int	free_all(t_var *shell)
{
	final_free_env(shell);
	final_free_cmd(shell);
	free_strs(shell->input, NULL);
	free(shell->pipe);
	shell->pipe = 0;
	free(shell->pids);
	shell->pids = 0;
	free(shell);
	shell = NULL;
	return (0);
}

void	final_free_env(t_var *shell)
{
	t_env	*env_ptr;

	while (shell->env)
	{
		env_ptr = shell->env;
		free_strs(env_ptr->name, NULL);
		free_strs(env_ptr->value, NULL);
		free(env_ptr);
		shell->env = shell->env->next;
	}
	shell->env = NULL;
}

void	final_free_cmd(t_var *shell)
{
	t_cmdlist	*cmd_ptr;

	while (shell->cmdlist)
	{
		cmd_ptr = shell->cmdlist;
		free_strs(cmd_ptr->brut, NULL);
		free_strs(cmd_ptr->cmd_path, cmd_ptr->cmd_arg);
		free_strs(cmd_ptr->redir_input, NULL);
		free_strs(cmd_ptr->redir_output, NULL);
		free_strs(cmd_ptr->delim_hdoc, NULL);
		free(cmd_ptr);
		shell->cmdlist = shell->cmdlist->next;
	}
	shell->cmdlist = NULL;
}

int	exit_minishell(t_var *shell, int exit_code)
{
	ft_putendl_fd("exit", 1, 0);
	if (shell != NULL)
		free_all(shell);
	exit (exit_code % 256);
}