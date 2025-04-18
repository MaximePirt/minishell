/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:22:57 by mpierrot          #+#    #+#             */
/*   Updated: 2024/10/17 10:22:57 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

# define MAX_COMMAND_SIZE 1024

typedef enum s_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_AND_OPERATOR,
	TOKEN_OR_OPERATOR,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_OUT_APPEND,
	TOKEN_REDIR_IN,
	TOKEN_HEREDOC,
	TOKEN_PARENTHESIS_OPEN,
	TOKEN_PARENTHESIS_CLOSE,
}	t_token_type;
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef enum s_ast_node_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_SUBSHELL,
	AST_REDIR_OUT,
	AST_REDIR_OUT_APPEND,
	AST_REDIR_IN,
	AST_HEREDOC,
}	t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	char				**value;
	int					is_last;
	int					in_pipe;
	int					heredoc_fd;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

// ########################################################
// #						PARSER							#
// ########################################################

int				build_ast(t_token **tokens,
					t_ast_node **root, t_ast_node **last_command);
t_ast_node		*parse_input(t_minishell *minishell, char *input);

int				process_command(t_token **tokens, t_ast_node **root,
					t_ast_node **last_command);
int				process_argument(t_token **current, t_ast_node *last_command);
int				process_pipe(t_token **tokens, t_ast_node **root,
					t_ast_node **last_command);
int				process_operator(t_token **tokens, t_ast_node **root,
					t_ast_node **last_command);
int				process_subshell(t_token **tokens, t_ast_node **root,
					t_ast_node **last_command);
int				process_heredoc(t_token **tokens, t_ast_node **root,
					t_ast_node **last_command, int is_last);
int				process_redirection(t_token **tokens, t_ast_node **root,
					t_ast_node **last_command, int is_last);
char			*check_input(char *input);
int				check_quotes_count(char *str);
char			*check_input_and_validate(t_minishell *minishell, char *input);
int				handle_token_errors(t_minishell *minishell,
					t_token *tokens, int error, t_ast_node *ast);
int				check_double_heredoc_happend(t_token *tokens);

// ########################################################
// #					TOKEN_MANAGER						#
// ########################################################

void			add_token(char ***tokens, int *token_count, char *token);
void			add_token_to_list(t_token **tokens,
					t_token_type type, char *value);
void			clear_token_list( t_token **token_list,
					char **tokens, int token_count);
int				token_is_logic_operator(t_token *token);
t_ast_node_type	get_redir_type(t_token_type type);

// ########################################################
// #						TOKENIZER						#
// ########################################################

void			tokenize(const char *input, t_token **token_list);
char			**extract_command_tokens(t_token **tokens);
char			*extract_quoted_token(char *input, int *index);
char			*handle_quotes(char *buffer, int *buffer_pos,
					char *input, int *index);
char			*handle_parentheses(char current_char, int *index);

// ########################################################
// #					Split_W_Quotes					#
// ########################################################

typedef struct s_tokenizer
{
	char	**tokens;
	int		token_count;
	char	*buffer;
	int		buf_pos;
	char	quote_char;
}	t_tokenizer;

t_tokenizer		init_tokenizer_split(const char *input);
int				is_operator_split(const char *input, int i, char quote_char);
char			**split_with_quotes(const char *input, int *count);

// ########################################################
// #						AST									#
// ########################################################

t_ast_node		*new_ast_node(t_ast_node_type type, char **command);
int				count_heredoc(t_ast_node *ast);
int				update_next_command(char *new_command, t_ast_node *ast);

#endif
