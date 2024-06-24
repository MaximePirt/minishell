/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 06:52:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/06/16 06:52:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handle the double quote (") operator
 *
 * @param int type
 * @param t_ast **tmp
 * @param char **args
 * @param int *i
 * @return int 1 if the double quote was handled, 0 otherwise
 */
static char	*handle_quote(t_minishell *minishell, int type, char *str)
{
	char	*res;

	res = NULL;
	if (type == TEXT_DOUBLE_QUOTE || type == VARIABLE)
		res = extract_variables(minishell, str);
	else if (type == TEXT_SINGLE_QUOTE)
		res = ft_strdup(str);
	return (res);
}

static char **get_args(t_minishell *minishell, t_ast *cmd)
{
	char			**args;
	t_ast			*tmp;
	unsigned int	size;
	int 			i;

	size = ast_len(cmd);
	args = ft_calloc(size + 2, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	args[i++] = ft_strdup(cmd->value);
	tmp = cmd->next;
	while (tmp)
	{
		args[i] = handle_quote(minishell, tmp->type, tmp->value);
		tmp = tmp->next;
		i++;
	}
	args[size] = 0;
	return (args);
}

/**
 * @brief Generate a command structure from an AST node
 *
 * @param t_minishell *minishell
 * @param t_ast *cmd
 * @return t_cmd *
 */
t_cmd	*command_maker(t_minishell *minishell, t_ast *cmd)
{
	t_cmd	*new_cmd;
	char	*path;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	//find the command in the PATH
	new_cmd->cmd_name = ft_strdup(cmd->value);
	path = get_path(cmd->value, minishell->env);
	if (!path)
		path = ft_strdup(cmd->value);
	new_cmd->cmd_exec = path;
	new_cmd->argv = get_args(minishell, cmd);
	new_cmd->argc = (int)ast_len(cmd);
	new_cmd->env = minishell->env;
	new_cmd->path = get_var_value(minishell->env, "PATH");
	new_cmd->fd_in = 0;
	new_cmd->fd_out = 1;
	new_cmd->exit_status = 0;
	return (new_cmd);
}