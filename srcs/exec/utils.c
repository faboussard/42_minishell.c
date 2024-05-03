/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:29:13 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/03 11:54:56 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	check_and_delete_if_tmp_file_exists(char *tmp_file)
{
	if (access(tmp_file, F_OK) == 0)
	{
		if (unlink(tmp_file) == -1)
			perror("");
	}
}

void	ft_init_pl(t_minishell *m, t_process_list *pl)
{
	m->status = 0;
	m->tmp_in = 0;
	pl->fd_in = -1;
	pl->fd_out = -1;
	pl->dev_null = 0;
	pl->paths = NULL;
	pl->good_path = NULL;
	pl->tab_paths = NULL;
}

void	ft_free_pl_paths(t_minishell *minishell)
{
	if (minishell->paths != NULL)
		free(minishell->paths);
	if (minishell->pl->good_path != NULL)
		free(minishell->pl->good_path);
	if (minishell->pl->tab_paths != NULL)
		ft_free_tab(&(minishell->pl->tab_paths));
}

char	**ft_tabdup(char **s, size_t len)
{
	char	**dest;
	size_t	i;

	i = 0;
	dest = ft_calloc(len + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = ft_strdup(s[i]);
		if (!dest[i])
		{
			ft_free_tab(&dest);
			return (NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
