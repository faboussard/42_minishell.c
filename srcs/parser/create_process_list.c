/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/19 09:43:37 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "parser.h"

void define_file_token(t_token_list **in_files_list, t_minishell *minishell, const t_token_list *iterator)
{
	t_token_list *new_token;

	new_token = ft_calloc(1, sizeof(t_token_list));
	if (new_token == NULL)
		exit_msg_minishell(minishell, "Malloc failed at define_file_token", ENOMEM);
	new_token->name = ft_strdup(iterator->name);
	if (new_token->name == NULL)
	{
		free_token(new_token);
		exit_msg_minishell(minishell, "Malloc failed at define_file_token", ENOMEM);
	}
	new_token->next = NULL;
	new_token->e_type = iterator->e_type;
	new_token->e_operator = iterator->e_operator;
	new_token->is_quoted_delimiter = iterator->is_quoted_delimiter;
	new_token->failed_expand = iterator->failed_expand;
	add_token_to_list(in_files_list, new_token);
}

void create_in_files_list(t_token_list **in_files_list, t_minishell *minishell)
{
	t_token_list	*iterator;
	t_token_list 	*next;

	iterator = minishell->list_tokens;
	while (iterator != NULL && iterator->e_operator != PIPE)
	{
		next = iterator->next;
		if (iterator->e_type == IN_FILE || iterator->e_type == DELIMITER)
			define_file_token(in_files_list, minishell, iterator);
		iterator = next;
	}
}

void create_out_files_list(t_token_list **out_files_list, t_minishell *minishell)
{
	t_token_list	*iterator;
	t_token_list 	*next;

	iterator = minishell->list_tokens;
	while (iterator != NULL && iterator->e_operator != PIPE)
	{
		next = iterator->next;
		if (iterator->e_type == OUT_FILE || iterator->e_type == APPEND_FILE)
			define_file_token(out_files_list, minishell, iterator);
		iterator = next;
	}
}

void create_process_list_node(t_process_list *new_pl, t_minishell *m)
{
	size_t nbr_cmds_letters_in_pipe;

	nbr_cmds_letters_in_pipe = count_letters_until_pipe(m->list_tokens);
	create_in_files_list(&(new_pl->in_files_list), m);
	create_out_files_list(&(new_pl->out_files_list), m);
	create_cmd_table_array(new_pl, nbr_cmds_letters_in_pipe, m);
}

