/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:04:36 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/19 21:16:29 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <stdbool.h>

#define MAX_LEN 4096

typedef struct s_cmdlist
{
	char				*brut;
	char				*cmd_path;
	char				**cmd_arg;
	enum e_type			type;
	char				*start;
	char				*end;
	char				*redir_input;	//filename or NULL
	char				*delim_hdoc;	//exit word or NULL
	char				*redir_output;	//filename or NULL
	int					flag_append;	//flag
	int					fd_in; // initialiser à 0
	int					fd_out; // initialiser à 1
	struct s_cmdlist	*next;
}					t_cmdlist;

enum e_type {
	NIL,
	WORD,
	SQ,
	DQ,
	TOKEN_CD,
	TOKEN_PATH,
	TOKEN_OPTION,
	TOKEN_STRING,
};

#endif

int	free_cmdlist(t_cmdlist **head);