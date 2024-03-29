/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorber <jlorber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:07:03 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/28 17:08:47 by jlorber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../Libft/libft.h"

# define MAX_LEN 4096

// //----------------global variable----------------//
extern struct s_data	g_data;
struct s_data
{
	int		exit_code;
	int		pid;
};

typedef struct s_cmdlist
{
	char				*brut;
	char				*cmd_path;
	char				**cmd_arg;
	char				*redir_input;
	char				*delim_hdoc;
	char				*redir_output;
	int					flag_append;
	int					fd_in;
	int					fd_out;
	struct s_cmdlist	*next;
}	t_cmdlist;

//----------------struct----------------//
typedef struct s_env {
	char			*name;
	char			*value;
	int				exists;
	int				exported;
	struct s_env	*next;

}	t_env;

typedef struct s_var {
	char		*input;
	t_cmdlist	*cmdlist;
	t_cmdlist	*current;
	char		*start;
	char		*end;
	char		*buf;
	char		*prompt;

	int			heredoc;
	int			child;
	int			*pipe;
	int			*pids;
	int			cmd_nbr;
	t_env		*env;
}	t_var;

//----------------minishell----------------//
t_var		*init_struct(char **envp);
t_env		*init_env(char **envp);
int			init_process(t_var *shell);
void		free_mem(t_var *shell);

//---------------parsing------------------//
int			parsing(t_var *shell);

//---------------parsing utils------------//
int			free_cmdlist(t_cmdlist **head);
t_cmdlist	*new_cmdnode(void);
char		*what_inside_sq(char **pos);
char		*replace_by_var(char **pos, t_env *env);
void		ft_concat(char **str, char *str2);

//------------- set redir ----------------//
void		set_redirs(t_cmdlist *ptr, t_var *shell);

//-------------split token----------------//
char		**split_token(char *s);

//-------------pars quotes----------------//
void		quotes_and_var(char **str, t_env *env, int in_dq);

//------------------envir------------------//
t_env		*find_export(char **tmp, t_var *shell);
char		**build_envp(t_env *env);
int			var_handler(t_cmdlist *cmd, t_var *shell);
int			var_handler2(char **tmp, t_var *shell);

//------------------built-in------------------//
int			exec_pwd(t_env *env, t_cmdlist *cmd);
int			exec_env(t_env *env);
int			exec_echo(t_cmdlist *cmd);
int			exec_exit(t_cmdlist *cmd, t_var *shell);
int			exec_cd(t_cmdlist *cmd, t_env *env);
int			exec_export(t_cmdlist *cmd, t_var *shell);
int			exec_export2(char **tmp, t_var *shell);
int			check_export(char **tmp, t_var *shell);
int			new_export(char **tmp, t_var *shell);
int			change_export(char **tmp, t_var *shell);
int			exec_unset(t_cmdlist *cmd, t_var *shell);

//------------------exec------------------//
int			which_command(t_var *shell, t_cmdlist *cmd);
void		sig_handler(int signum);
int			ms_execute(t_var *shell);
void		redirection(t_var *shell, t_cmdlist *ptr);
int			one_cmd(t_var *shell);
int			pipex(t_var *shell);
int			redirect_io(int input, int output);
int			path_finder(t_var *shell);
char		*get_cmd(char *cmd, t_var *shell);
int			file_handler(t_cmdlist *cmd, t_var *shell);
int			redir_first_last(t_var *shell, t_cmdlist *cmd);
int			redir_other(t_var *shell, t_cmdlist *cmd);
int			ft_unlink_heredocs(t_var *shell, t_cmdlist *cmd);

//----------------check----------------//
int			error_manager(int error);

//----------------utils----------------//
void		close_fds(t_var *shell);
void		close_pipe_fds(t_var *shell);
int			free_strs(char *str, char **strs);
char		**build_envp(t_env *env);
int			number_of_cmd(t_var *shell);
int			free_all(t_var *shell);
void		final_free_cmd(t_var *shell);
void		final_free_env(t_var *shell);
int			exit_minishell(t_var *shell, int exit_code);
int			is_builtin(char *cmd);
void		reinit_struct(t_var *shell);

#endif
