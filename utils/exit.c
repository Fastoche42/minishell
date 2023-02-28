/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:32:15 by jlorber           #+#    #+#             */
/*   Updated: 2023/02/28 01:30:48 by rtazlaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_all(t_var *shell)
{
	final_free_env(shell);
	final_free_cmd(shell);
	free_strs(shell->input, NULL);
	free_strs(shell->prompt, NULL);
	free(shell->pipe);
	shell->pipe = 0;
	free(shell->pids);
	shell->pids = 0;
	rl_clear_history();
	if (shell)
	{
		free(shell);
		shell = NULL;
	}
	return (0);
}

void	final_free_env(t_var *shell)
{
	t_env	*env_ptr;
	t_env	*env_tmp;

	env_tmp = shell->env;
	while (env_tmp)
	{
		env_ptr = env_tmp;
		env_tmp = env_tmp->next;
		free_strs(env_ptr->name, NULL);
		free_strs(env_ptr->value, NULL);
		if (env_ptr)
			free(env_ptr);
	}
	shell->env = NULL;
}

void	final_free_cmd(t_var *shell)
{
	t_cmdlist	*cmd_ptr;
	t_cmdlist	*cmd_tmp;

	cmd_tmp = shell->cmdlist;
	while (cmd_tmp)
	{
		cmd_ptr = cmd_tmp;
		cmd_tmp = cmd_tmp->next;
		free_strs(cmd_ptr->brut, NULL);
		free_strs(cmd_ptr->cmd_path, cmd_ptr->cmd_arg);
		free_strs(cmd_ptr->redir_input, NULL);
		free_strs(cmd_ptr->redir_output, NULL);
		free_strs(cmd_ptr->delim_hdoc, NULL);
		if (cmd_ptr)
			free(cmd_ptr);
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
