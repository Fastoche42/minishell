/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:07:03 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/26 10:54:13 by marvin           ###   ########.fr       */
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
//# include "parsing.h"

#define MAX_LEN 4096

// //----------------global variable----------------//
extern int	g_exit_code;

enum e_type { // utilité ?
	NIL,
	WORD,
	SQ,
	DQ,
	TOKEN_CD,
	TOKEN_PATH,
	TOKEN_OPTION,
	TOKEN_STRING
};

typedef struct s_cmdlist
{
	char				*brut;
	char				*cmd_path;
	char				**cmd_arg;
	enum e_type			type;
	char				*redir_input;	//filename or NULL
	char				*delim_hdoc;	//exit word or NULL
	char				*redir_output;	//filename or NULL
	int					flag_append;	//flag
	int					fd_in; // initialiser à 0
	int					fd_out; // initialiser à 1
	struct s_cmdlist	*next;
}	t_cmdlist;

//----------------struct----------------//
typedef struct s_env {
	char			*name;		// gauche du =
	char			*value;		// droite du =
	int				exists;		// pas deleted
	int				exported;	// exportee ou non
	struct s_env	*next;
	
}	t_env;

typedef struct s_var {
	char		*input;
	t_cmdlist	*cmdlist;
	t_cmdlist	*current;
	char		*start;
	char		*end;
	char		*buf;

	int			heredoc; // heredoc flag, à incrémenter pour chaque heredoc
	int			child; // index
	int			*pipe;
	int			*pids; // process IDs (nécessaire au forking)
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

//------------------envir------------------//
t_env	*find_export(char **tmp, t_var *shell);
char	**build_envp(t_env *env);
int		var_handler(t_cmdlist *cmd, t_var *shell);


//------------------exec------------------//
int		which_command(t_var *shell, t_cmdlist *cmd); // mise à jour 10/01/2023
void	sig_handler(int signum);
int		ms_execute(t_var *shell);
int		exec_pwd(t_env *env); // mise à jour 05/01/2023
int		exec_env(t_env *env); // mise à jour 10/01/2023
int		exec_echo(t_cmdlist *cmd); // mise à jour 05/01/2023
int		exec_exit(t_cmdlist *cmd, t_var *shell);
int		exec_cd(t_cmdlist *cmd, t_env *env); // mise à jour 10/01/2023
int		exec_export(t_cmdlist *cmd, t_var *shell); // mise à jour 10/01/2023
int		exec_unset(t_cmdlist *cmd, t_var *shell); // mise à jour 10/01/2023
void	redirection(t_var *shell, t_cmdlist *ptr); // toujours nécessaire ?
int		one_cmd(t_var *shell);
int  	pipex(t_var *shell);
int		redirect_io(int input, int output);
char 	*get_cmd(char *cmd, t_var *shell);
int		file_handler(t_cmdlist *cmd, t_var *shell);
int		redir_first_last(t_var *shell, t_cmdlist *cmd);
int		redir_other(t_var *shell, t_cmdlist *cmd);
int		ft_unlink_heredocs(t_var *shell, t_cmdlist *cmd);

//----------------check----------------//
int		error_manager(int error);

//----------------utils----------------//
void	close_fds(t_var *shell);
void	close_pipe_fds(t_var *shell);
int		free_strs(char *str, char **strs);
char	**build_envp(t_env *env);
int		number_of_cmd(t_var *shell);
int		free_all(t_var *shell);
int		exit_minishell(t_var *shell, int exit_code);
int		is_builtin(char *cmd);
void	reinit_struct(t_var *shell);

#endif
