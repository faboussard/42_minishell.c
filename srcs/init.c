/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/18 14:44:58 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "utils.h"

static int	check_arguments(int ac, char **av)
{
	if (ac != 1 && ac != 3)
		return (-1);
	if (ac == 3)
	{
		if (!av[1] || ft_strcmp(av[1], "-c") != 0 || !av[2] || av[2][0] == '\0')
			return (-1);
	}
	return (0);
}

void	ft_init_minishell(t_minishell *minishell, int ac, char **av)
{
	ft_bzero(minishell, (sizeof(t_minishell)));
	if (check_arguments(ac, av) == -1)
		exit_msg(minishell,
			"Wrong arguments. Usage: ./minishell- c \"input line\"", -1);
	minishell->total_commands = 1;
}

bool	is_interactive(t_minishell *minishell, int ac)
{
	if (ac == 3)
	{
		minishell->interactive = false;
		return (false);
	}
	else
	{
		minishell->interactive = true;
		return (true);
	}
}
