/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:28:29 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/19 21:16:20 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_cmdlist(t_cmdlist **head)
{
	t_cmdlist	*ptr;

	while (*head)
	{
		ptr = *head;
		free(ptr->brut);
		//free_strs(NULL, ptr->cmd_arg);
		//free(ptr->cmd_path);
		free(ptr->redir_input);
		free(ptr->redir_output);
		*head = (*head)->next;
		free(ptr);
	}
	head = NULL; // utile ??
	return (0);
}

static t_cmdlist	*new_cmdnode(void)
{
	t_cmdlist	*node;

	node = malloc(sizeof(t_cmdlist));
	if (!node)
		return (NULL);
	node->brut = NULL;
	node->cmd_path = NULL;
	node->redir_input = NULL;
	node->delim_hdoc = NULL;
	node->redir_output = NULL;
	node->flag_append = 0;
	node->fd_in = 0;
	node->fd_out = 1;
	node->next = NULL;
	return (node);
}

/*
//==================================================================
typedef struct shell {
	char **argv;
	int argc;
	char *redir_input;
	char *redir_output;
	int flag_append;
	char *delim_hdoc;
	char result[MAX_LEN];
} shell;

void init_shell(shell *sh) {
	sh->argv = NULL;
	sh->argc = 0;
	sh->redir_input = NULL;
	sh->redir_output = NULL;
	sh->flag_append = 0;
	sh->delim_hdoc = NULL;
}

static void parse_one_cmd(t_cmdlist ptr)
{
	int i = 0, j = 0, k = 0, l = 0, m = 0, n = 0;
	char buffer[MAX_LEN];
	char var[MAX_LEN];
	int	i; // parcours de la chaine
	int len;

	len = strlen(ptr->brut);
	i = 0;
	while (i < len)
	{
		// Skip whitespaces
		while (ptr->brut[i] == ' ' || ptr->brut[i] == '\t')
			i++;
		j = i;
		// Handle redirection
		if (ptr->brut[i] == '<' || ptr->brut[i] == '>')
		{
			char redir = ptr->brut[i];
			int j = i + 1;
			// Skip whitespaces
			while (ptr->brut[j] == ' ' || ptr->brut[j] == '\t')
				j++;
			if (ptr->brut[j] == '>')
			{
				sh->flag_append = 1;
				j++;
				// Skip whitespaces
				while (ptr->brut[j] == ' ' || ptr->brut[j] == '\t')
					j++;
			}
			// Skip whitespaces
			while (ptr->brut[j] == ' ' || ptr->brut[j] == '\t')
				j++;
			if (ptr->brut[j] == '\0')
			{
				// Error: expected file name after redirection operator
				strcpy(sh->result, "Error: expected file name after redirection operator\n");
				return;
			}
			k = j;
			while (ptr->brut[k] != '\0' && ptr->brut[k] != ' ' && ptr->brut[k] != '\t')
				k++;
			// Store the redirection file name
			char *file_name = (char *) malloc(k - j + 1);
			memcpy(file_name, &ptr->brut[j], k - j);
			file_name[k - j] = '\0';
			if (redir == '<')
			{
				// Input redirection
				sh->redir_input = file_name;
			}
			else
			{
				// Output redirection
				sh->redir_output = file_name;
				if (redir == '>')
					sh->flag_append = 0;
				else
				{
					// redir == '>>'
					sh->flag_append = 1;
				}
			}
			i = k - 1;
		}
		else if (ptr->brut[i] == ''')
		{
			// Single quote handling
			int j = i + 1;
			while (ptr->brut[j] != ''' && ptr->brut[j] != '\0')
				j++;
			if (ptr->brut[j] == '\0')
			{
				// Error: unterminated single quote
				strcpy(sh->result, "Error: unterminated single quote\n");
				return;
			}
			// Copy the single-quoted string to the argument array
			char *arg = (char *) malloc(j - i);
			memcpy(arg, &ptr->brut[i + 1], j - i - 1);
			arg[j - i - 1] = '\0';
			sh->argv[sh->argc++] = arg;
			i = j;
		}
		else
		{
			// Normal argument handling
		int j = i + 1;
		while (ptr->brut[j] != '\0' && ptr->brut[j] != ' ' && ptr->brut[j] != '\t') {
			j++;
		}
		// Copy the argument to the argument array
		char *arg = (char *) malloc(j - i + 1);
		memcpy(arg, &ptr->brut[i], j - i);
		arg[j - i] = '\0';
		sh->argv[sh->argc++] = arg;
		i = j - 1;
	}
}
//==================================================================
*/

static int expand_dollar(t_cmdlist *ptr, t_env *env)
{
	e_type type;
	char *start;
	char *end;
	char	*str;
	char	*str2;
	char	*var;

	type = NIL;
	start = ptr->brut;
	end = start;
	str = NULL;
	while (*end)
	{
		if (*end == '\'' && type != DQ)
			while (*(end+1) != '\'')
				end++;
			end++;
		else if (*end == '$')
		{
			if ((*(end+1) == '?') || (isalpha(*(end+1))))
			{
				str2 = ft_strndup (*start, (end - start));
				str = ft_realloc(str, strlen(str) + strlen(str2) + 1);
                ft_strcat(str, str2);
				free (str2);
				if (*(end+1) == '?')
					str2 = ft_itoa(g_exit_code);
				else
					str2 = replace_by_var(end);
				str = ft_realloc(str, strlen(str) + strlen(str2) + 1);
                ft_strcat(str, str2);
				free (str2);
			}
		}
		end++;
	}
	free (ptr->brut);
	ptr->brut = buffer;
}

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

	expand_dollar(ptr, env);
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
		if (*end == '$' && type != SQ)
		{
			end++;
			if (*end == '?')
			{
				str = ft_itoa(g_exit_code);
				// join à cmd_arg
			}
		}
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
}

static int parse_pipes(t_var *shell)
{
	int in_single_quotes;
	int in_double_quotes;
	const char *start;
	const char *end;
	t_cmdlist *current;
	char *token;
	int length;
	int	nbn = 0; // tempoR pour debog

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
			nbn++;

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
	nbn++;
	printf("nb noeuds: %d\n", nbn);
	return (0);
}

int	parsing(t_var *shell)
{
	t_cmdlist	*ptr; //pointeur de parcours

	// parse "|" avoiding quotes + fill cmdlist
	if (!parse_pipes(shell))
		return (1);

	ptr = shell->cmdlist;
	while (ptr)
	{
		if (parse_one_cmd(ptr, shell->env));
		 	// erreur rencontree => free cmdlist
			return(1);
		ptr = ptr->next;
	}
	// temporaire commamde line : (ls -a | wc -l) ; (exit) ; ...
 /*
	shell->cmdlist = new_cmdnode();
	if (!shell->cmdlist)
		return (0);

	ptr = shell->cmdlist;
	ptr->cmd_path = "/bin/ls";
	ptr->cmd_arg = ft_split("ls -l", ' ');

	ptr->next = new_cmdnode();
	ptr = ptr->next;
	ptr->cmd_path = "/usr/bin/head";
	ptr->cmd_arg = ft_split("head -3", ' ');

	ptr->next = new_cmdnode();
	ptr = ptr->next;
	ptr->cmd_path = "/bin/cat";
	ptr->cmd_arg = ft_split("cat -e", ' ');
*/
	return (0);
}
