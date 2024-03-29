/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h              			                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_SIGNALS_H
#define MINISHELL_SIGNALS_H

void	set_signals_interactive(void);
void	signal_print_newline(int signal);
void	set_signals_noninteractive(void);
void	ignore_sigquit(void);

#endif //MINISHELL_SIGNALS_H
