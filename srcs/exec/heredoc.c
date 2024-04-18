/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:20:54 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/11 10:41:39 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"

void check_and_delete_if_tmp_file_exists(char *tmp_file)
{
	if (access(tmp_file, F_OK) == 0)
	{
		if (unlink(tmp_file) == -1)
			perror("");
	}
}

void handle_expand(t_minishell *m, char *input)
{
	char **split_space;
	char *input_after_expand;

	split_space = ft_split(input, ' ');
	if (split_space == NULL)
		exit_msg_minishell(m, "Fatal : malloc failed at handle expand", -1);
	input_after_expand = expand_variables(m, split_space);
	if (input_after_expand != NULL)
		ft_putstr_fd(input_after_expand, m->fd_in);
	else
		ft_putstr_fd(input, m->fd_in);
	if (input_after_expand  != NULL)
		free(input_after_expand);
	if (split_space != NULL)
		ft_free_tab(split_space);
}

char *expand_variables(t_minishell *m, char **split_space)
{
	char *input_after_expand = ft_calloc(1, 1);
	input_after_expand[0] = '\0';
	int count;

	count = -1;
	for (int i = 0; split_space[i]; i++)
	{
		if (is_quoted_variable(split_space[i]))
			handle_quoted_variable(m, &input_after_expand, split_space[i]);
		else
			handle_regular_variable(m, &input_after_expand, split_space[i], &count, &i);
	}
	return input_after_expand;
}

void handle_quoted_variable(t_minishell *m, char **input_after_expand, char *token)
{
	char *expanded;

	expanded= expand_sigil(token, m);
	if (expanded != token)
		*input_after_expand = ft_strjoin(*input_after_expand, expanded);
}

void handle_regular_variable(t_minishell *m, char **input_after_expand, char *token, int *count, int *i)
{
	char *temp = get_non_variable_part(token);

	if (temp != NULL)
	{
		(*count)++;
		if (*count != 0 && *count == *i)
			*input_after_expand = ft_strjoin(*input_after_expand, " ");
		*input_after_expand = ft_strjoin(*input_after_expand, temp);
		free(temp);
	}
	char **split_dollar = ft_split(token, '$');
	if (split_dollar == NULL)
		exit_msg_minishell(m, "Malloc failed at handle expand", -1);
	for (int j = 0; split_dollar[j]; j++)
	{
		handle_quoted_variable(m, input_after_expand, split_dollar[j]);
		free(split_dollar[j]);
	}
	free(split_dollar);
}

char *get_non_variable_part(char *string)
{
	int i = 0;
	char *temp;

	while (string[i] && string[i] != '$')
		i++;
	if (i != 0)
	{
		temp = ft_substr(string, 0, i);
		return temp;
	}
	return NULL;
}

int is_quoted_variable(char *string)
{
	if (string[0] == '$' && (string[1] == '\'' || string[1] == '\"'))
		return 1;
	return 0;
}

static void writing_in_heredoc(t_minishell *m, char *limiter)
{
	size_t limiter_len;
	size_t input_len;
	char *input;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
	input = get_next_line(STDIN_FILENO);
	input_len = ft_strlen(input) - 1;
	if (input_len == limiter_len && !ft_strncmp(input, limiter,
												limiter_len))
	{
		free(input);
		close(m->fd_in);
		exit(0);
	}
	handle_expand(m, input);
	free(input);
	}
}

void here_doc(t_minishell *m, char *limiter)
{
	check_and_delete_if_tmp_file_exists(HERE_DOC_TMP_FILE);
	m->fd_in = open(HERE_DOC_TMP_FILE, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (m->fd_in < 0)
	{
		perror("No /tmp/ directory found");
		return;
	}
	// A CHANGER, pas d'exit du minishell
	m->pid1 = m_safe_fork(m);
	if (m->pid1 == 0)
	writing_in_heredoc(m, limiter);
	else
	{
	while (waitpid(-1, &(m->status), 0) && errno != 10);
	close(m->fd_in);
	}
}
