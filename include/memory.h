/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:24:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/28 12:24:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "parsing.h"

// ########################################################
// #						ALLOC						  #
// ########################################################

t_minishell	*alloc_minishell(void);
int			alloc_dirinfo(t_minishell *minishell);

// ########################################################
// #						FREE						  #
// ########################################################

void		free_minishell(t_minishell *minishell);
void		free_tokens(t_token *tokens);
void		free_ast(t_ast *ast);
void		free_cmd(t_cmd *cmd);

#endif
