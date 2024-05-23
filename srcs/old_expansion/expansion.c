/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/11 17:01:49 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "parser.h"

// HELLO
void ft_lsti_insert_after(t_token_list **current, t_token_list *new_token)
{
	if (current == NULL || *current == NULL || new_token == NULL)
		return;
	new_token->next = (*current)->next;
	(*current)->next = new_token;
}

void process_dollar_token(t_minishell *minishell, t_token_list **list, int single_quote_count, int double_quote_count)
{
	char *expanded_string;

	if (ft_strncmp((*list)->next->name, "?", 2) == 0)
		change_name_to_status(minishell, *list);
	else
	{
		if (single_quote_count % 2 != 0 && double_quote_count % 2 == 0)
			return ;
		if (!ft_isalnum((*list)->next->name[0]) && (*list)->next->name[0] != '_' && double_quote_count % 2 == 0)
			(*list)->e_operator = 0;
		else
		{
			define_to_delete_tokens(list);
			expanded_string = expand_sigil((*list)->next->name, minishell);
			if (expanded_string != (*list)->next->name)
			{
				change_to_expansion(minishell, list, &expanded_string);
				return;
			}
			else
				define_to_delete_tokens(list);
		}
	}
}

void handle_dollar_files(t_minishell *minishell, t_token_list **list)
{
	char *expanded_string;

	expanded_string = NULL;
	(*list) = (*list)->next;
	if ((*list)->next == NULL)
		return;
	while ((*list) && (*list)->e_operator == IS_SPACE)
		(*list) = (*list)->next;
	if (*list && (*list)->e_operator == DOLLAR)
	{
		expanded_string = expand_sigil((*list)->next->name, minishell);
		if (expanded_string != (*list)->next->name)
		{
			change_to_expansion(minishell, list, &expanded_string);
			return;
		}
		else
			(*list)->failed_expand = true;
	}
}

void handle_dollar(t_minishell *minishell, t_token_list **iterator, int *single_quote_count, int *double_quote_count)
{
	if ((*iterator)->next == NULL)
		return;
	if ((is_redirect_token((*iterator)->next) && (*iterator)->next->next != NULL &&
		(*iterator)->next->next->e_operator == IS_SPACE)
	    || s_quote_after_d_quote_and_dollar(iterator, *single_quote_count, *double_quote_count))
	{
		*iterator = (*iterator)->next;
		return;
	}
	//cette partie gere le cas ou on a un single quote apres le dollar sans avoir dautre quote avant, il faut lenlever. et ne pas expand
	if ((*iterator)->next->e_operator == SINGLE_QUOTE && (*single_quote_count % 2 == 0) && (*double_quote_count % 2 == 0))
	{
		define_to_delete_tokens(iterator);
		*iterator = (*iterator)->next;
		return;
	}
	add_quotes_count(*iterator, single_quote_count, double_quote_count);
	process_dollar_token(minishell, iterator, *single_quote_count, *double_quote_count);
}

void expand_tokens(t_minishell *minishell, t_token_list *iterator, int *single_quote_count, int *double_quote_count)
{
	int cheat_number;

	cheat_number= -1;
	while (iterator != NULL && iterator->next != NULL)
	{
		if (iterator->e_operator == HERE_DOC)
			handle_delimitor(&iterator);
		else if (iterator->e_operator == DOUBLE_QUOTE && (*double_quote_count % 2 == 0) && (*single_quote_count % 2 != 0))
			update_quote_counts(iterator, single_quote_count, &cheat_number);
		else if (iterator->e_operator == DOUBLE_QUOTE || iterator->e_operator == SINGLE_QUOTE)
			update_quote_counts(iterator, single_quote_count, double_quote_count);
		else if (iterator->e_operator == INPUT_REDIRECT || iterator->e_operator == OUTPUT_REDIRECT
		|| iterator->e_operator == APPEND)
			handle_dollar_files(minishell, &iterator);
		else if (iterator->e_operator == DOLLAR && iterator->next != NULL)
			handle_dollar(minishell, &iterator, single_quote_count, double_quote_count);
		if (iterator == NULL)
			break ;
		iterator = iterator->next;
	}
}

void expand_for_heredoc(t_minishell *minishell, t_token_list *iterator, int *single_quote_count, int *double_quote_count)
{
	while (iterator != NULL && iterator->next != NULL)
	{
		if (iterator->e_operator == DOLLAR && iterator->next != NULL)
		{
			if (is_redirect_token(iterator->next) && iterator->next->next != NULL &&
				iterator->next->next->e_operator == IS_SPACE)
			{
				iterator->e_operator = 0;
				iterator = iterator->next;
				continue;
			}
			process_dollar_token(minishell, &iterator, *single_quote_count, *double_quote_count);
		}
		if (iterator == NULL)
			break ;
		iterator = iterator->next;
	}
}


void expander(t_minishell *minishell, t_token_list **list, bool is_here_doc)
{
	t_token_list *iterator;
	int single_quote_count;
	int double_quote_count;

	single_quote_count = 0;
	double_quote_count = 0;
	iterator = *list;
	if (is_here_doc)
		expand_for_heredoc(minishell, iterator, &single_quote_count, &double_quote_count);
	else
		expand_tokens(minishell, iterator, &single_quote_count, &double_quote_count);
}