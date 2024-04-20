/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:18:22 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/20 13:40:09 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_fd_infile(t_minishell *m, t_token_list *in_files_list)
{
	if (in_files_list->e_type == DELIMITER)
		m->fd_in = open(HERE_DOC_TMP_FILE, O_RDONLY);
	else if (in_files_list->e_type == IN_FILE)
		m->fd_in = open(in_files_list->name, O_RDONLY);
	else
		m->fd_in = STDIN_FILENO;
	if (m->fd_in < 0)
	{
		if (in_files_list->e_type == DELIMITER)
			perror("minishell: /tmp/.tmp_heredoc");
		else
			print_name(m, in_files_list->name);
		m->status = 1;
		m->process_list->dev_null = 1;
		m->fd_in = open("/dev/null", O_RDONLY);
		if (m->fd_in < 0)
		{
			ft_putendl_fd("No /dev/null/ found", 2);
			return (1);
		}
	}
	return (0);
}
/*
		mbernard@z1r9p2:/usr$ cd cdvwev
		bash: cd: cdvwev: No such file or directory
		mbernard@z1r9p2:/usr$ echo $?
		1
*/

int	open_fd_outfile(t_minishell *m, t_process_list *pl, char *out)
{
	if (pl->out_files_token->e_type == OUT_FILE)
		m->fd_out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (pl->out_files_token->e_type == APPEND_FILE)
		m->fd_out = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		m->fd_out = STDOUT_FILENO;
	if (m->fd_out < 0)
	{
		print_name_and_give_status(m, out, 1);
		return (1);
	}
	return (0);
}

int	dup_original_fds(t_minishell *m, int *in, int *out, size_t nb_cmds)
{
	if (m->process_list->in_files_token->e_type != NO_TYPE || nb_cmds > 1)
		*in = dup(STDIN_FILENO);
	if (m->process_list->out_files_token->e_type != NO_TYPE || nb_cmds > 1)
		*out = dup(STDOUT_FILENO);
	if (*in == -1 || *out == -1)
	{
		ft_putendl_fd("minishell : dup error", 2);
		m->status = 1;
		return (1);
	}
	return (0);
}

void	close_original_fds(t_minishell *m, int *in, int *out, size_t nb_cmds)
{
	if (m->process_list->in_files_token->e_type != NO_TYPE || nb_cmds > 1)
	{
		if (dup2(*in, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			m->status = 1;
		}
		close(*in);
	}
	if (m->process_list->out_files_token->e_type != NO_TYPE || nb_cmds > 1)
	{
		if (dup2(*out, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			m->status = 1;
		}
		close(*out);
	}
}

void	close_and_redirect_pipe_to_stdin(t_minishell *m)
{
	if (m->pipe_fd[WRITE_END] >= 0)
		close(m->pipe_fd[WRITE_END]);
	if (m->fd_in >= 0)
		close(m->fd_in);
	m->fd_in = m->pipe_fd[READ_END];
	m_safe_dup2(m, m->pipe_fd[READ_END], STDIN_FILENO);
}
