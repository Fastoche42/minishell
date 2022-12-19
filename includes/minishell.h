/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:07:03 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/11 18:24:42 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../Libft/libft.h"
# include "parsing.h"

//----------------global variable----------------//
extern pid_t	g_pid;

//----------------struct----------------//
typedef struct s_path {
	char			*str;
	struct s_path	*next;
}	t_path;

typedef struct s_env {
	char			*name;		// gquche du =
	char			*value;		// droite du =
	int				exists;		// pas deleted
	int				exported;	// exportee ou non
	struct s_env	*next;
	
}	t_env;

typedef struct s_var {
	int			fd_input;
	int			fd_output;
	int			infile;
	int			outfile;
	int			save_input;
	int			save_output;
	int			prev_pipe; // ?
	char		*input;

	t_cmdlist	*cmdlist;		// ptr vers liste de commande => exec Morgan
	char		*cmd_path;
	char		**cmd_arg;
	char		**cmd_env;
	char		*redir_input;
	char		*redir_hdoc;
	char		*redir_output;
	char		*redir_append;

	int			heredoc; // heredoc flag, à incrémenter pour chaque heredoc
	int			child; // index
	int			*pipe;
	int			*pids; // process IDs (nécessaire au forking)
	int			cmd_nbr; // doit être initialisé pour initialiser les pipes et les pids
	t_path		*path;
	char		**envp;
	t_env		*env;

	char		**cmd_access;	//split de $PATH (non nécessaire, le parsing de PATH est fait avant l'exécution)
}	t_var;

//----------------minishell----------------//
t_var	*init_struct(char **envp);
t_env	*init_env(char **envp);
int		init_process(t_var *shell);
void	free_mem(t_var *shell);

//---------------parsing------------------//
int		ms_parsing(t_var *shell);

//----------------exec----------------//
void	which_command(t_var *shell, t_cmdlist *cmd); // mise à jour 16/12/2022
void	handler_sig(int signum);
int		ms_execute(t_var *shell);
char	*exec_pwd(char **envp); // mise à jour 16/12/2022
void	exec_env(char **envp); // mise à jour 16/12/2022
void	exec_echo(t_cmdlist *cmd); // mise à jour 16/12/2022
int		exec_exit(t_var *shell); // je ne crois pas quelle soit nécessaire
int		exec_cd(t_cmdlist *cmd); // mise à jour 16/12/2022
int		exec_export(t_var *shell, char **env);
void	exec_unset(t_cmdlist *cmd, char **env);
void	redirection(t_var *shell, t_cmdlist *ptr); // toujours nécessaire ?
int		number_of_cmd(t_var *shell);

int  	pipex(t_var *shell);
char 	*get_cmd(char *cmd, t_var *shell);



//----------------check_error----------------//
int		verif_exit(char *cmd);
int		verif_export(char *cmd);
int		check_path_cmd(t_var *shell, char **var);
int		error_manager(int error);
int		check_export(char *str);

//----------------utils----------------//
int		count_args(t_var *shell);
void	find_cmd(t_var *shell, char **var);
int		nb_var_in_env(char **env);
char	*modif_input(char *input);
int		ft_free_splited(char **str);

#endif
