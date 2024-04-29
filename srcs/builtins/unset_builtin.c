/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/29 11:55:24 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

bool	is_valid_env_var_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] != '\0')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	ft_unset(t_minishell *minishell, char **args)
{
	int	i;
	int var_index;
	int	ret;

	i = 1;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			print_cmd_perror_no_strerror(args[i], "unset: invalid parameter name");
			ret = EXIT_FAILURE;
		}
		else
		{
			var_index = get_env_var_index(minishell, minishell->envp_table, args[i]);
			printf("unset: %s\n", args[i]);
			printf("%d\n", var_index);
			if (var_index != -1)
				remove_env_var(minishell, var_index);
		}
		i++;
	}
	return (ret);
}