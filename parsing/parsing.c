/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:28:29 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/24 02:02:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int expand_dollar(t_cmdlist *ptr, t_env *env)
{
	char	*start;
	char	*end;
	char	*str;
	char	*str2;

	start = ptr->brut;
	end = start;
	str = NULL;
	while (*end)
	{
		if (*end == '\'')
		{
			while (end[1] != '\'')
				end++;
			end++;
		}
//		skip_car(&end, '\'');
		else if (*end == '$')
		{
			if (*(end+1) == '?' || ft_isalpha(*(end+1)) || *(end+1) == '_')
			{
				if (end > start)
					ft_concat(&str, ft_strndup (start, (end - start)));
				end++;
				if (*end == '?')
					str2 = ft_itoa(g_exit_code);
				else
					str2 = replace_by_var(&end, env);
				ft_concat(&str, str2);
				start = end + 1;
			}
		}
		end++;
	}
	if (end > start)
		ft_concat(&str, ft_strndup (start, (end - start)));
	free (ptr->brut);
	ptr->brut = str;
	return (0);
}

static char	*create_token(t_var *shell, char *start, char *end, int last)
{
	int length;
	char *token;

	length = end - start;
	token = malloc(length + 1);
	if (!token)
		return (NULL);
	ft_memcpy(token, start, length);
	token[length] = '\0';
	if (last)
		return (token);
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

static int	parse_pipes(t_var *sh)
{
	int	in_quotes; // 0, 1 pour ', 2 pour "
	t_cmdlist	*current;

	sh->cmdlist = new_cmdnode();
	sh->current = sh->cmdlist;
	in_quotes = 0;
	sh->start = sh->input;
	sh->end = sh->start;
	while (*sh->end)
	{
		if (*sh->end == '\'' && in_quotes != 2)
			in_quotes = 1 - in_quotes;
		else if (*sh->end == '"' && in_quotes != 1)
			in_quotes = 2 - in_quotes;
		else if (*sh->end == '|' && !in_quotes)
		{
			sh->current->brut = create_token(sh, sh->start, sh->end, 0);
			sh->start = sh->end + 1;
		}
		sh->end++;
	}
	sh->current->brut = create_token(sh, sh->start, sh->end, 1);
	if (in_quotes)
		return (error_manager(20));
	return (0);
}

int	parsing(t_var *shell)
{
	t_cmdlist	*ptr; //pointeur de parcours

	if (parse_pipes(shell))
		return (1);
	ptr = shell->cmdlist;
	while (ptr)
	{
		//if (set_redirs(ptr))
		//	return (1);
		ptr->cmd_arg = (split_token(ptr->brut));
		if (!(ptr->cmd_arg))
			return (1);
		//if (expand_dollar(ptr, shell->env))
		//	return (1);
		//if (parse_one_cmd(ptr, shell->env))
		//	return (1);
		ptr = ptr->next;
	}
	// temporaire commamde line : (ls -a | wc -l) ; (exit) ; ...
	/*
	shell->cmdlist = new_cmdnode();
	if (!shell->cmdlist)
		return (0);

	ptr = shell->cmdlist;
	//ptr->cmd_path = "/bin/ls";
	ptr->cmd_arg = ft_split("env", ' ');

	ptr->next = new_cmdnode();
	ptr = ptr->next;
	//ptr->cmd_path = "/usr/bin/head";
	ptr->cmd_arg = ft_split("grep PATH", ' ');

	ptr->next = new_cmdnode();
	ptr = ptr->next;
	//ptr->cmd_path = "/usr/bin/head";
	ptr->cmd_arg = ft_split("grep bin", ' ');

	ptr->next = new_cmdnode();
	ptr = ptr->next;
	//ptr->cmd_path = "/usr/bin/head";
	ptr->cmd_arg = ft_split("wc", ' ');
*/
	return (0);
}
