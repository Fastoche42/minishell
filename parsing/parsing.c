/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorber <jlorber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:28:29 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/28 18:49:08 by jlorber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	dequotes_on_redir(t_cmdlist *ptr, t_env *env)
{
	char	*tmp;

	if (ptr->redir_input)
	{
		tmp = ptr->redir_input;
		quotes_and_var(&tmp, env, 0);
		free_strs(ptr->redir_input, NULL);
		ptr->redir_input = tmp;
	}
	if (ptr->redir_output)
	{
		tmp = ptr->redir_output;
		quotes_and_var(&tmp, env, 0);
		free_strs(ptr->redir_output, NULL);
		ptr->redir_output = tmp;
	}
	if (ptr->delim_hdoc)
	{
		tmp = ptr->delim_hdoc;
		quotes_and_var(&tmp, env, 0);
		free_strs(ptr->delim_hdoc, NULL);
		ptr->delim_hdoc = tmp;
	}
	return (0);
}

static int	dequotes_cmd_arg(t_cmdlist *ptr, t_env *env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (ptr->cmd_arg[++i])
	{
		tmp = ptr->cmd_arg[i];
		quotes_and_var(&tmp, env, 0);
		free_strs(ptr->cmd_arg[i], NULL);
		ptr->cmd_arg[i] = tmp;
	}
	return (0);
}

static char	*create_token(t_var *shell, char *start, char *end)
{
	int		length;
	char	*token;

	length = end - start;
	token = malloc(length + 1);
	if (!token)
		return (NULL);
	ft_memcpy(token, start, length);
	token[length] = '\0';
	if (!shell->cmdlist)
	{
		shell->cmdlist = new_cmdnode();
		shell->current = shell->cmdlist;
	}
	else
	{
		shell->current->next = new_cmdnode();
		shell->current = shell->current->next;
	}
	return (token);
}

/*		in_quotes; // 0, 1 pour ', 2 pour " .  */
static int	parse_pipes(t_var *sh)
{
	int	in_quotes;

	in_quotes = 0;
	sh->start = sh->input;
	sh->end = sh->start;
	while (*sh->end)
	{
		if (sh->end[0] == '\'' && in_quotes != 2)
			in_quotes = 1 - in_quotes;
		else if (sh->end[0] == '"' && in_quotes != 1)
			in_quotes = 2 - in_quotes;
		else if (sh->end[0] == '|' && !in_quotes)
		{
			sh->buf = create_token(sh, sh->start, sh->end);
			sh->current->brut = sh->buf;
			sh->start = sh->end + 1;
		}
		sh->end++;
	}
	if (in_quotes)
		return (error_manager(20));
	sh->buf = create_token(sh, sh->start, sh->end);
	sh->current->brut = sh->buf;
	sh->current = NULL;
	return (0);
}

int	parsing(t_var *shell)
{
	t_cmdlist	*ptr;

	if (ft_onlyspace(shell->input))
		return (1);
	if (parse_pipes(shell))
		return (1);
	ptr = shell->cmdlist;
	while (ptr)
	{
		set_redirs(ptr, shell);
		ptr->cmd_arg = (split_token(ptr->brut));
		if (!(ptr->cmd_arg))
			return (error_manager(99));
		if (dequotes_cmd_arg(ptr, shell->env))
			return (error_manager(21));
		if (dequotes_on_redir(ptr, shell->env))
			return (error_manager(21));
		ptr = ptr->next;
	}
	return (0);
}
