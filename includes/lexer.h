/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:26:16 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/13 16:26:32 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include "libft.h"
#include "minishell.h"

enum e_token_type
{
	NO_TYPE = 0,
	COMMAND = 1,
	ARGUMENT = 2,
	PATH_FILE = 3,
	OPERATOR = 4,
	TO_APPEND = 5,
	SUBSHELL = 6,
};

enum e_token_operators
{
	NO_OPERATOR = 0,
	OPEN_PARENTHESES = 1,
	CLOSE_PARENTHESES = 2,
	PIPE = 3,
	INPUT_REDIRECT = 4,
	OUTPUT_REDIRECT = 5,
	HERE_DOC = 6,
	APPEND = 7,
	DOUBLE_QUOTE = 8,
	SINGLE_QUOTE = 9,
};

enum e_token_builtin
{
	NO_BUILTIN = 0,
	CD = 1,
	LS = 2,
	ECHO = 3,
	PWD = 4,
	EXPORT = 5,
	UNSET =	6,
	ENV = 7,
	EXIT = 8
};

typedef struct s_token
{
    char					*name;
    enum e_token_type		e_type;
    enum e_token_builtin	e_builtin;
    enum e_token_operators	e_operator;
    struct s_token          *next;
}	t_token;


/****************** SPLIT_READLINE ******************/

char	**split_with_quotes_management(char *string);

/******************* EXPANSION *******************/

int	parentheses_error(const char *string);
int parentheses_on_arg(char *string);

/****************** LEXER ******************/

void	define_token_types(enum e_token_type type, enum e_token_builtin builtin, enum e_token_operators operator, t_token *new_token);

/****************** BUILTIN ******************/

bool	get_builtin_token(t_token *new_token, char *string);

/********************* ENV_VARIABLES *********************/


#endif //LEXER_H
