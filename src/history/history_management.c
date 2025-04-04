/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:54:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/07/19 04:04:29 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new history element
 *
 * @param char *cmd
 * @param t_history *older
 * @param t_history *newer
 * @return t_history *
 */
static t_history	*history_create(char *cmd, t_history *older,
							t_history *newer)
{
	t_history	*history;

	history = (t_history *) ft_calloc(1, sizeof(t_history));
	if (!history)
		return (NULL);
	history->cmd = cmd;
	history->older = older;
	history->newer = newer;
	return (history);
}

/**
 * @brief Add command to history file and memory
 * 			If the command is the same as the last one, it will not be added
 * 			to memory but will still be added to the file for log purposes
 *
 * @param t_minishell *minishell Minishell structure
 * @param char *cmd Command to add
 * @param int fs save to file if 1 otherwise 0
 * @return int 0 if added, -1 if failed
 */
int	history_add(t_minishell *minishell, char *cmd, int fs)
{
	t_history	*new;
	int			fd;

	if (!minishell->history->older || !minishell->history->older->cmd
		|| ft_strcmp(minishell->history->older->cmd, cmd) != 0)
	{
		new = history_create(ft_strdup(cmd),
				minishell->history->older, minishell->history);
		if (minishell->history->older)
			minishell->history->older->newer = new;
		minishell->history->older = new;
		minishell->history_size++;
	}
	if (!fs)
		return (0);
	fd = history_goto_file(minishell);
	if (fd < 0)
		return (-1);
	ft_fprintf(fd, "%s\n", cmd);
	close(fd);
	return (0);
}

/**
 * @brief Reset the history file and memory
 *
 * @param t_minishell *minishell
 * @return void
 */
void	history_reset(t_minishell *minishell)
{
	t_history	*tmp;
	int			trunc;

	while (minishell->history->older)
	{
		tmp = minishell->history->older;
		free(minishell->history->cmd);
		free(minishell->history);
		minishell->history = tmp;
	}
	free(minishell->history->cmd);
	free(minishell->history);
	minishell->history = history_create(NULL, NULL, NULL);
	trunc = open(HISTORY_FILE, O_WRONLY | O_TRUNC);
	if (trunc == -1)
	{
		terminal_print(BOLDRED"Error: "RESET""HISTORY_FILE" open failed",
			1, STDOUT_FILENO);
		return ;
	}
	close (trunc);
}

/**
 * @brief Print the content of history file to the terminal
 *
 * @param t_minishell *minishell Minishell structure
 * @param int fd file descriptor to print to
 * @return void
 */
void	history_print(t_minishell *minishell, int fd)
{
	t_history		*history;
	char			*tmp;
	int				i;
	unsigned int	j;

	history = minishell->history;
	while (history && history->older)
		history = history->older;
	i = 0;
	while (history && history->newer)
	{
		terminal_print("    ", 1, fd);
		tmp = ft_itoa(i);
		terminal_print(tmp, 0, fd);
		free(tmp);
		j = -1;
		while (++j < 4 - ft_nbrlen(i))
			terminal_print(" ", 0, fd);
		terminal_print(history->cmd, 0, fd);
		history = history->newer;
		i++;
	}
	terminal_print("", 1, fd);
}
