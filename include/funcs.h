/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:24:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/28 12:24:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_H
# define FUNCS_H

# include "minishell.h"

// ########################################################
// #						HISTORY						  #
// ########################################################

void	reset_history(void);
void	add_to_history(char *cmd);
int		get_history_file(void);

// ########################################################
// #						MAIN						  #
// ########################################################

// ########################################################
// #						PARSING						  #
// ########################################################

// ########################################################
// #						COMMAND						  #
// ########################################################

#endif