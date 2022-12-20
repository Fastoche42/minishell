/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:04:36 by fl-hote           #+#    #+#             */
/*   Updated: 2022/12/20 12:26:04 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_cmdlist
{
	char				*cmd_path;
	char				**cmd_arg;
	char				**cmd_env;
	int					type;
	char				*redir_input;	//filename or NULL
	char				*delim_hdoc;	//exit word
	char				*redir_output;	//filename
	int					flag_append;	//filename
	int					fd_in;	//voir comment parsing affecte ces 2 int
	int					fd_out;
	struct s_cmdlist	*next;
//	struct s_var		*shell; //a initialiser ?? turn around ??
}					t_cmdlist;

#endif