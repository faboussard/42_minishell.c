/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:29 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/07 08:50:46 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "utils.h"

# ifndef READ_END
#  define READ_END 0
# endif

# ifndef WRITE_END
#  define WRITE_END 1
# endif

//---------------------------- SAFE UTILS -----------------------------//
pid_t	m_safe_fork(t_minishell *minishell);
void	m_safe_dup2(t_minishell *minishell, int old_fd, int new_fd);
bool	safe_pipe(t_minishell *m);
void	close_pipes(int *pipe_fd);
void	close_fds(int fd_in, int fd_out);
//--------------------------- PATHS -----------------------------------//
void	set_paths(t_minishell *m, char **env);
void	set_good_path_cmd(t_minishell *m, t_process_list *pl, char *cmd);
char	*join_sep(t_minishell *m, char *s1, char *s2, char sep);
//--------------------------- FD MANAGEMENT ---------------------------//
int		open_fd_infile(t_minishell *m, t_process_list *pl, char *name, int *fd_to_use);
int		open_fd_outfile(t_minishell *m, t_process_list *pl, char *out);
void	close_and_redirect_pipe_to_stdin(t_minishell *m, t_process_list *pl);
//--------------------------- HERE_DOC --------------------------------//
void	here_doc(t_minishell *m, t_token_list *limiter, int *fd_to_use, t_process_list *pl);
//--------------------------- UTILS -----------------------------------//
void	ft_init_pl(t_minishell *m, t_process_list *pl);
void	ft_free_pl_paths(t_minishell *minishell, t_process_list *pl);
void	init_before_next_prompt(t_minishell *m);
//--------------------------- CHILD CARE ------------------------------//
void	exec_several_cmds(t_minishell *m, t_process_list *p_list);
//--------------------------- EXEC ------------------------------------//
void	my_execve(t_minishell *m, t_process_list *pl);
bool	exec_builtin(t_minishell *m, char *cmd, char **cmd_table);
int		handle_in_out(t_minishell *m, t_process_list *pl, int *fd_in);
//--------------------------- ERRORS ------------------------------------//
void	print_name(t_minishell *m, char *name);
void	print_name_and_msg(t_minishell *m, char *name, char *msg);
void	exit_command_not_found(t_minishell *m, char *name, t_process_list *pl);
void	exit_is_a_directory(t_minishell *m, char *name, t_process_list *pl);
void	print_name_and_exit_perror(t_minishell *m, char *name, int error_code);
void	print_name_and_exit_msg(t_minishell *m, char *name, char *msg, int err);
void	print_name_and_give_status(t_minishell *m, char *name, int err);
void	malloc_error_with_exit(t_minishell *m);
void	malloc_error_no_exit(t_minishell *m);
#endif
