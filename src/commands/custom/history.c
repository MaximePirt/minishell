/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 06:52:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/06/16 06:52:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print the history of commands, support for -c and -s flags
 *
 * @param t_cmd *cmd Command structure
 * @param t_minishell *minishell Minishell structure
 * 			(it contain history chain list)
 * @return int Exit code
 */
int	command_history(t_cmd *cmd, t_minishell *minishell)
{
	char	*tmp;

	if (cmd->argc == 1)
		history_print(minishell, cmd->output_fd);
	else if (contain_flag(cmd->args, 'c'))
	{
		terminal_print("History cleared\n", 1, cmd->output_fd);
		history_reset(minishell);
	}
	if (contain_flag(cmd->args, 's') && cmd->argc >= 3)
	{
		tmp = ft_strjoin_list((const char **)(cmd->args + 2), " ");
		if (!tmp)
			return (1);
		history_add(minishell, tmp, 1);
		free(tmp);
		terminal_print("", 1, cmd->output_fd);
	}
	return (0);
}
