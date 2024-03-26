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
#include "minishell.h"
#include "utils.h"

static bool check_arguments(t_minishell *minishell, int ac, char **av)
{
	if (ac != 1 && ac != 3)
		exit_msg(minishell, "Wrong number of arguments. Usage: ./minishell (-c + command)", -1);
	if (ac == 3)
	{
		minishell->interactive = false;
		if (!av[1] || ft_strncmp(av[1], "-c", 2) != 0 || !av[2] || av[2][0] == '\0')
			exit_msg(minishell, "Wrong arguments. Usage: ./minishell (-c + command)", -1);
	}
	else
		minishell->interactive = true;
	return (true);
}

int main(int ac, char **av, char **envp)
{
	t_minishell 	minishell;

	if (!ft_init_minishell(&minishell, envp))
		exit_msg(&minishell, "Error: ft_init_minishell", -1);
	if (!check_arguments(&minishell, ac, av) || )

	create_token_chain_list(&minishell, string);
	print_token(minishell.list_tokens); //DELETE
	create_envp_hashmap(&minishell, envp);
	print_envp_dict(minishell.hashmap_environment->dict_chain); //DELETE
	create_tables(&minishell);
	ft_printf("************ print cmd_table ************\n\n");
	print_array(minishell.cmd_table);  //DELETE
	ft_printf("********************** print HM table **********************\n\n");
	print_array(minishell.envp_table);  //DELETE
	free_minishell(&minishell);
	return (0);
}


