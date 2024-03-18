/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                			                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "utils.h"




//int minishell_init(t_minishell *minishell, char **envp, char argv_zero)
//{
//	ft_bzero(minishell, (sizeof * minishell));
//	//setgoodpath with command. fonction melodie.
//}


void create_lists(t_minishell *minishell, char **string, char *envp[])
{
	minishell->list_tokens = get_list_tokens(string);
	print_token(minishell->list_tokens);
	minishell->hm_env_variables = get_hm_env_variables(envp);
	print_hashmap(minishell->hm_env_variables);
}

int main()
{
	/******* dans int main(int ac, char **av, char **env) *****/
	char			*string[] = {"echo", "ls", ">>", "output.txt", NULL};
	char			*envp[] = {
			"PATH=/bin:/usr/bin",
			"HOME=/home/user",
			"USER=user",
			NULL
	};
	/******* dans int main(int ac, char **av, char **env) *****/
	t_minishell 	minishell;
//	tmp = minishell_init(&minishell, envp, argv[0]);
	create_lists(&minishell, string, envp);
	create_double_array(&minishell, minishell.list_tokens);
	print_array(minishell.args);
	free_minishell(&minishell);
	return (0);
}


