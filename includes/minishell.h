/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/07 08:47:24 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef MALLOC_FAILED
#  define MALLOC_FAILED -1
# endif

# ifndef SUCCESSFULLY_ADDED
#  define SUCCESSFULLY_ADDED 0
# endif

# ifndef HERE_DOC_TMP_FILE
#  define HERE_DOC_TMP_FILE "/tmp/.tmp_heredoc"
# endif

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef PROMPT
#define PROMPT "\001\e[27m\002>>> \001\e[0m\e[45m\002 Minishell>$ \001\e[0m\002"
# endif

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include "lexer.h"
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_envp			t_envp_list;
typedef struct s_token			t_token_list;
typedef struct s_minishell		t_minishell;
typedef struct s_process_list	t_process_list;
typedef struct s_fake_env		t_fake_env;

typedef struct s_minishell
{
	bool						interactive;
	pid_t						pid1;
	pid_t						pid2;
	int 						SHLVL;
	int							status;
	int							pipe_fd[2];
	int							tmp_in;
	int							history_count;
	char						*user_input;
	char						target_path[PATH_MAX];
	char						current_path[PATH_MAX];
	char						old_pwd[PATH_MAX];
	char						*paths;
	char						**envp_table;
	t_token_list				*list_tokens;
	t_envp_list					*list_envp;
	t_process_list				*pl;
	t_fake_env					*fake_env;
	size_t						total_commands;
	size_t						total_size_envp;
}								t_minishell;

typedef struct s_envp
{
	char						*value;
	char						*target;
	size_t						value_size;
	size_t						target_size;
	struct s_envp				*next;
}								t_envp_list;

typedef struct s_process_list
{
	t_token_list				*in_files_token;
	t_token_list				*out_files_token;
	int							fd_in;
	int							fd_out;
	char						*paths;
	char						*good_path;
	char						**tab_paths;
	char						**cmd_table;
	bool						dev_null;
	struct s_process_list		*next;
}								t_process_list;

typedef struct s_fake_env
{
	char *target_;
	char *target_SHLVL;
	char *target_PWD;
	char *content_;
	char *content_SHLVL;
	char *content_PWD;
}								t_fake_env;

/********************************** INIT MINISHELL ***************************/

bool							is_interactive(t_minishell *minishell, int argc, char **argv);

/*********************************** CREATE CHAINS ***************************/

void							create_token_chain_list(t_minishell *minishell,
									char *string);
void							create_envp_hashmap(t_minishell *minishell,
									char **envp);

/********************************** CREATE TABLES ***************************/

void execute_cmds(t_minishell *minishell,
                  size_t nb_cmds);

//// expand heredoc ///

void	handle_expand(t_minishell *m, t_process_list *pl, char *input);

int	set_or_get_last_status(int status, int flag);

#endif
