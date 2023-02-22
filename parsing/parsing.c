/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:28:29 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/22 12:02:40 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
static int find_redir(t_cmdlist *ptr)
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
			skip_car (&end, '\'');
		else if (*end == '"')
			skip_car (&end, '"');
		else if (*end == '>')
		{
			if (ptr->redir_output) // multi non géré
				return (error_manager(21));
			if (end > start)
				ft_concat(&str, ft_strndup (start, (end - start)));
			end++;
			if (*end == '>')
				ptr->flag_append = 1;
			//ptr->redir_output = find_redirfile(&end);
		}
		end++;
	}
	return (0);
}

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
			skip_car(&end, '\'');
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

	/*
static int parse_one_cmd(t_cmdlist *ptr, t_env *env)
{
	enum e_type	type;
	int in_single_quotes;
	int in_double_quotes;
	char *start;
	char *end;
	char	*str;
	int	a;
	int length;

	type = NIL;
	in_single_quotes = 0;
	in_double_quotes = 0;
	start = ptr->brut;
	end = start;
	a = 0; // arg counter max 20
	ptr->cmd_arg = malloc(sizeof(char));
	ptr->cmd_arg = 0;
	while (*end)
	{
		if (type != SQ && type != DQ)
		{
			if (*end == '\'') //début ' => stocker jusquà '
			{
				if (type != SQ)
					type = SQ;
				else
					type = NIL
			}
			else if (*end == '"' && type != SQ)
			{
				if (type != DQ)
					type = DQ;
				else
					type = NIL
			}
			else if (*end == '<' && type != SQ && type != DQ)
			else if (*end == '$' && type != SQ && type != DQ)
			else if (*end == ' ' && !in_single_quotes && !in_double_quotes)
			{
				length = end - start;
				token[t] = malloc(length + 1);
				memcpy(token, start, length);
				token[length] = '\0';
			}
		}
		end++;
	}
	return (0);
}
	*/

static int parse_pipes(t_var *shell)
{
	int in_single_quotes;
	int in_double_quotes;
	const char *start;
	const char *end;
	t_cmdlist *current;
	char *token;
	int length;

	in_single_quotes = 0;
	in_double_quotes = 0;
	start = shell->input;
	end = start;
	while (*end)
	{
		if (*end == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (*end == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (*end == '|' && !in_single_quotes && !in_double_quotes)
		{
			length = end - start;
			token = malloc(length + 1);
			memcpy(token, start, length);
			token[length] = '\0';
			if (!shell->cmdlist)
			{
				shell->cmdlist = new_cmdnode();
				current = shell->cmdlist;
			}
			else
			{
				current->next = new_cmdnode();
				current = current->next;
			}
			current->brut = token;

			start = end + 1;
		}
		end++;
	}
	length = end - start;
	token = malloc(length + 1);
	memcpy(token, start, length);
	token[length] = '\0';
	if (!shell->cmdlist)
	{
		shell->cmdlist = new_cmdnode();
		current = shell->cmdlist;
	}
	else
	{
		current->next = new_cmdnode();
		current = current->next;
	}
	current->brut = token;
	if (in_single_quotes || in_double_quotes)
		return (error_manager(20));
	return (0);
}

int	parsing(t_var *shell)
{
	t_cmdlist	*ptr; //pointeur de parcours
/*
	if (parse_pipes(shell))
		return (1);

	ptr = shell->cmdlist;
	while (ptr)
	{
		if (expand_dollar(ptr, shell->env))
			return (1);
		//if (find_redir(ptr))
		//	return (1);
		ptr->cmd_arg = (split_token(ptr->brut));
		if (!(ptr->cmd_arg))
			return (1);
		//if (parse_one_cmd(ptr, shell->env))
		 	// erreur rencontree => free cmdlist
		//	return (1);
		ptr = ptr->next;
	}
	// temporaire commamde line : (ls -a | wc -l) ; (exit) ; ...
 */
	shell->cmdlist = new_cmdnode();
	if (!shell->cmdlist)
		return (0);

	ptr = shell->cmdlist;
	//ptr->cmd_path = "/bin/ls";
	ptr->cmd_arg = ft_split("ls -l", ' ');

	ptr->next = new_cmdnode();
	ptr = ptr->next;
	//ptr->cmd_path = "/usr/bin/head";
	ptr->cmd_arg = ft_split("grep PATH", ' ');

	ptr->next = new_cmdnode();
	ptr = ptr->next;
	//ptr->cmd_path = "/usr/bin/head";
	ptr->cmd_arg = ft_split("wc -l", ' ');

	return (0);
}
