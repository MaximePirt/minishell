/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <pierrot.maxime.pro@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 01:18:56 by mpierrot          #+#    #+#             */
/*   Updated: 2024/10/24 01:18:56 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\nminishell: heredoc interrupted"
			"by Ctrl+C\n", STDERR_FILENO);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
}

void	setup_heredoc_parent_signals(void)
{
	struct sigaction	sa_parent;

	sigemptyset(&sa_parent.sa_mask);
	sa_parent.sa_flags = 0;
	sa_parent.sa_handler = parent_signal_handler;
	sigaction(SIGINT, &sa_parent, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Run the heredoc logic in a fork and handle signals in the child
 *
 * @param t_minishell *minishell
 * @param char *delimiter
 * @param int *output_fd
 * @return int 1 on success, 0 on failure
 */
void	setup_heredoc_child_signals(void)
{
	struct sigaction	sa_child;

	ft_memset(&sa_child, 0, sizeof(sa_child));
	sa_child.sa_flags = 0;
	sa_child.sa_handler = heredoc_signal_handler;
	sigemptyset(&sa_child.sa_mask);
	sigaction(SIGINT, &sa_child, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	write_and_cleanup_heredoc(t_heredoc_info *heredoc_info, int fd)
{
	if (!write_heredoc(heredoc_info))
	{
		close(fd);
		ft_tabfree(heredoc_info->texts);
		free(heredoc_info);
		exit(1);
	}
	close(fd);
	ft_tabfree(heredoc_info->texts);
	free(heredoc_info);
	exit(0);
}
