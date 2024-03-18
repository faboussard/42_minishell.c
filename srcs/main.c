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
<<<<<<< HEAD
#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "utils.h"

t_node *get_list_tokens(char *string)
{
	t_node 	*list_tokens;

	list_tokens = NULL;
	transform_to_token(string, &list_tokens);
	print_token(list_tokens);
	token_rework(list_tokens);
	return (list_tokens);
}


//int minishell_init(t_minishell *minishell, char **envp, char argv_zero)
//{
//	ft_bzero(minishell, (sizeof * minishell));
//	//setgoodpath with command. fonction melodie.
//}


int main()
{
	/******* dans int main(int ac, char **av, char **env) *****/
	char			*string; //char **argv
	char			*envp[] = {
			"PATH=/bin:/usr/bin",
			"HOME=/home/user",
			"USER=user",
			NULL
	};
//	char 			argv[0];
	/******* dans int main(int ac, char **av, char **env) *****/
	t_minishell 	minishell;
//	int 			tmp;

	string = "echo ls >> output.txt";
//	tmp = minishell_init(&minishell, envp, argv[0]);
	minishell.list_tokens = get_list_tokens(string);
	print_token(minishell.list_tokens);
	minishell.hm_env_variables = get_hm_env_variables(envp);
	print_hashmap(minishell.hm_env_variables);
	free_minishell(&minishell);
=======
#include "../libft/inc/libft.h"
#include <stdio.h>

void	is_delimiter(void)
{
	printf("hello word !");
}

int	main(void)
{
	is_delimiter();
>>>>>>> master
	return (0);
}
