/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:28:29 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/27 13:22:22 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	dequotes_cmd_arg(t_cmdlist *ptr, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ptr->cmd_arg[i])
	{
		tmp = ft_strdup(ptr->cmd_arg[i]);
		if (quotes_and_var(&tmp, env, 0))
			return (1);
		free (ptr->cmd_arg[i]);
		ptr->cmd_arg[i] = tmp;
		i++;
	}
	if (ptr->redir_input)
	{
		tmp = ft_strdup(ptr->redir_input);
		quotes_and_var(&tmp, env, 0);
		if (!tmp)
			return (1);
		free (ptr->redir_input);
		ptr->redir_input = tmp;
	}
	if (ptr->redir_output)
	{
		tmp = ft_strdup(ptr->redir_output);
		quotes_and_var(&tmp, env,0);
		if (!tmp)
			return (1);
		free (ptr->redir_output);
		ptr->redir_output = tmp;
	}
	if (ptr->delim_hdoc)
	{
		tmp = ft_strdup(ptr->delim_hdoc);
		quotes_and_var(&tmp, env, 0);
		if (!tmp)
			return (1);
		free (ptr->delim_hdoc);
		ptr->delim_hdoc = tmp;
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

	if (parse_pipes(shell))
		return (1);
	ptr = shell->cmdlist;
	while (ptr)
	{
		set_redirs(ptr, shell);
		//printf("brut:[%s]\n", ptr->brut);
		ptr->cmd_arg = (split_token(ptr->brut));
		if (!(ptr->cmd_arg))
			return (error_manager(99));
		if (dequotes_cmd_arg(ptr, shell->env))
			return (error_manager(21));
		ptr = ptr->next;
	}
	return (0);
}
