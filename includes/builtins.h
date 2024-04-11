/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/11 11:35:46 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "minishell.h"
# include "utils.h"

int ft_exit_builtin(t_minishell *minishell, t_token_list *command);
int	ft_env(t_minishell *minishell);
int	ft_setenv(t_minishell *minishell);
int	ft_unsetenv(t_minishell *minishell);
int	ft_cd(t_minishell *minishell, t_token_list *command);
int	ft_echo(t_minishell *minishell);
int	ft_pwd(t_minishell *minishell);
int	ft_export(t_minishell *minishell);
int	ft_unset(t_minishell *minishell);

#endif // BUILTINS_H