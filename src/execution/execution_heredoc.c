/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <julthoma@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:51:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/10/05 23:51:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

/**
 * @brief Load the heredoc info
 *
 * @param t_minishell *minishell
 * @param int *pipes
 * @param char *delimiter
 * @return t_heredoc_info*
 */
static t_heredoc_info	*load_heredoc_info(t_minishell *minishell,
											int *pipes, char *delimiter)
{
	t_heredoc_info	*heredoc_info;
	char			*tmp;

	heredoc_info = malloc(sizeof(t_heredoc_info));
	if (!heredoc_info)
		return (NULL);
	heredoc_info->minishell = minishell;
	heredoc_info->delimiter = ft_strdup(delimiter);
	tmp = parse_quotes(delimiter);
	if (ft_strlen(delimiter) != ft_strlen(tmp))
		heredoc_info->expend_var = 0;
	else
		heredoc_info->expend_var = 1;
	free(heredoc_info->delimiter);
	heredoc_info->delimiter = tmp;
	heredoc_info->pipes = pipes;
	heredoc_info->texts = ft_tabnew(0);
	if (!heredoc_info->texts)
	{
		free(heredoc_info->delimiter);
		free(heredoc_info);
		return (NULL);
	}
	return (heredoc_info);
}

int	handle_heredoc_parent_process(t_minishell *minishell, int *tmp_pipe,
							pid_t pid, int *output_fd)
{
	int	status;

	setup_heredoc_parent_signals();
	close(tmp_pipe[1]);
	waitpid(pid, &status, 0);
	*output_fd = tmp_pipe[0];
	minishell->exit_code = g_exit_code;
	if (minishell->exit_code == 130)
	{
		close(*output_fd);
		return (0);
	}
	else
		minishell->exit_code = 0;
	return (1);
}

/**
 * @brief Handle the signal in the parent process
 * 			to set the exit code to 130 on SIGINT
 *
 * @param int sig
 */
void	parent_signal_handler(int sig)
{
	if (sig == SIGINT)
		g_exit_code = 130;
}

void	handle_heredoc_child_process(t_minishell *minishell,
								int *tmp_pipe, char *delimiter)
{
	t_heredoc_info	*heredoc_info;

	setup_heredoc_child_signals();
	heredoc_info = load_heredoc_info(minishell, tmp_pipe, delimiter);
	if (!heredoc_info)
	{
		close_all_fds(minishell->opened_fds);
		exit(2);
	}
	close(tmp_pipe[0]);
	read_heredoc(heredoc_info);
	free(heredoc_info->delimiter);
	close_all_fds(minishell->opened_fds);
	free_minishell(heredoc_info->minishell);
	write_and_cleanup_heredoc(heredoc_info, tmp_pipe[1]);
}

int	run_heredoc(t_minishell *minishell, char *delimiter, int *output_fd)
{
	pid_t	pid;
	int		tmp_pipe[2];

	g_exit_code = 0;
	if (pipe(tmp_pipe) == -1)
		return (0);
	pid = fork();
	if (pid < 0)
	{
		close(tmp_pipe[0]);
		close(tmp_pipe[1]);
		return (0);
	}
	if (pid == 0)
		handle_heredoc_child_process(minishell, tmp_pipe, delimiter);
	return (handle_heredoc_parent_process(minishell, tmp_pipe, pid, output_fd));
}
