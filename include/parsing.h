/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:24:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/28 12:24:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

typedef enum {
	PIPE,
	FULL_COMMAND,
	COMMAND,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	ARGUMENT,
	FLAG,
    VARIABLE,
	TEXT_SINGLE_QUOTE,
	TEXT_DOUBLE_QUOTE,
	UNKNOWN
}	t_type;

typedef struct s_token
{
	t_type	type;
	char	*value;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	char			*value;
	int				type;
	struct s_ast	*next;
	struct s_ast	*parent;
	struct s_ast	*children;
	struct s_ast	*prev;
}	t_ast;

// ########################################################
// #						PARSER						  #
// ########################################################

t_ast		*parse_input(t_minishell *minishell, char *input);

// ########################################################
// #						TOKENIZER					  #
// ########################################################

t_token		*create_token(t_type type, char *value);
t_ast		*tokenize(t_ast *ast, char *arg);
void		extract_args(t_ast	*ast, char *full_command);


// ########################################################
// #						AST						  #
// ########################################################

t_ast		*create_ast(t_type type, char *value);
void		ast_add_back(t_ast *head, t_ast *ast);
void		ast_add_children(t_ast *ast, t_ast *children);

// ########################################################
// #						DEBUG						  #
// ########################################################

void	print_tokens(t_token *tokens);
void	print_ast(t_ast *ast);

#endif
