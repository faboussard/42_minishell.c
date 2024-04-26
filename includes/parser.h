/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/09 15:07:54 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "minishell.h"

/*************************token_list_utils**************************/

void ft_list_remove_if_same_type(t_token_list **begin_list, void *data_ref, int (*cmp)());
void ft_list_remove_if_same_op(t_token_list **begin_list, void *data_ref, int (*cmp)());

/************************* join_tokens.c **************************/
void join_tokens(t_minishell *minishell, t_token_list **list);
void join_between_quotes(t_minishell *minishell, t_token_list **list);
void join_between_spaces(t_minishell *minishell, t_token_list **list);
void join_between_quotes_handler(t_minishell *minishell, t_token_list **list, enum e_token_operators op);
char *join_all(t_minishell *minishell, t_token_list **list);
/************************* join_tokens_utils.c **************************/

void change_token_name(t_minishell *minishell, t_token_list **list, char *new_name);
int check_if_more_tokens(t_token_list **list, enum e_token_operators op);

/************************* token_requlif.c **************************/

void define_heredoc_and_append(t_minishell *minishell, t_token_list **list);
void	define_operators(t_token_list *list_tokens);
void	define_builtins(t_token_list *list_tokens);
void	to_infile_or_outfile(t_token_list *list_tokens);
void	arg_to_command(t_token_list *list_tokens);

/************************** parser  **************************/

int parse_input(t_minishell *minishell);
void	token_requalification(t_token_list *list_tokens);
void	*ft_free_all_alloc(char **strs_array, size_t start);
void token_rework(t_minishell *minishell);
int cmp(int op1, int op2);

/**************************** parse tokens **************************/

void			create_process_list(t_minishell *minishell);
t_process_list	*create_process_list_node(t_process_list *new_process_list,
					t_minishell *minishell);
void			create_envp_table(t_minishell *minishell);
void create_cmd_table_array(t_process_list *new_process_list, size_t size, t_minishell *minishell);

/****************** OPERATORS ******************/

bool			get_operator_token(t_token_list *new_token, char *string);
bool			is_redirect_token(t_token_list *token);

/********************* envp.c **************************/
t_envp_list		*create_envp_list(char **envp, t_minishell *minishell);

/********************* expansion_utils.c ****************************/
void expander(t_minishell *minishell, t_token_list **list);
void handle_delimitor(t_token_list **iterator);
char *expand_sigil(char *string, t_minishell *minishell);
char *expand_sign(char *string, char *temp);

int check_special_char_after_expand(char *string, char *string2);

/********************* expansion.c ****************************/
char *expand_variables(t_minishell *m, char **split_space);
void handle_quoted_variable(t_minishell *m, char **input_after_expand, char *token);
void handle_regular_variable(t_minishell *m, char **input_after_expand, char *token, int *count, int *i);
bool is_quoted_variable(char *token);
char	*get_non_variable_part(t_minishell *m,char *string);
void change_name_to_status(t_minishell *minishell, t_token_list *iterator);

/********************* check_syntax **************************/
bool check_quotes(t_minishell *minishell);
bool print_quote_syntax_error(enum e_token_operators operator);
bool print_operator_syntax_error(t_token_list *token);


#endif // PARSER_H
