/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:57:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/10/12 20:57:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the path and free the paths if correct
 *
 * @param char *path
 * @param char **paths
 * @return int 1 if the path is correct, 0 otherwise
 */
static int	check_path(char *path)
{
	if (access(path, X_OK) == 0)
		return (1);
	free(path);
	return (0);
}

/**
 * @brief Check if the env is valid
 *
 * @param char **env
 * @return int 1 if the env is valid, 0 otherwise
 */
static int	is_valid_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Get the path of the command to execute
 *
 * @param char *cmd
 * @param char **envp
 * @return char* the path of the command
 */
char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*cmd_path;
	char	**paths;
	char	*tmp;

	if (access(cmd, X_OK) == 0 || !is_valid_env(envp))
		return (NULL);
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ":");
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (check_path(cmd_path))
		{
			ft_tabfree(paths);
			return (cmd_path);
		}
	}
	ft_tabfree(paths);
	return (NULL);
}
