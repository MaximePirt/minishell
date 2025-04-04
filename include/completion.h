/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 03:46:00 by mpierrot          #+#    #+#             */
/*   Updated: 2024/10/17 10:15:17 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H

// ########################################################
// #					TAB_COMPLETION						#
// ########################################################

int		tab_manager(t_minishell *minishell, char *new);
int		tab_completion(t_minishell *minishell, char **input);
void	autocomplete_print(t_minishell *minishell, t_dict *dict, char **input);
void	prompt_completion(t_minishell *minishell, char **input);
int		tab_action(t_minishell *minishell, char **input);
int		creation_tab_dict(t_minishell *minishell, char *str);
int		tab_input_protection(t_minishell *minishell, char *new);
// ########################################################
// #					PRINT_BRANCH						#
// ########################################################
void	print_branch(t_dict *dict);
void	stress_print(t_minishell *minishell, t_dict *dict);

// ########################################################
// #						DICTIONNARY						#
// ########################################################

int		creation_dict(t_minishell *minishell);

// ########################################################
// #					NEED IN LIB							#
// ########################################################
void	repeat_str(char *key, int x);

// ########################################################
// #							BST							#
// ########################################################

t_dict	*insert_node(t_dict *root, t_dict *node, char *key, char *value);

t_dict	*create_node(char *key, char *value);
t_dict	*search_node(t_dict *root, char *key);
t_dict	*move_in_bst(t_dict *dict, int key);
void	cut_node(t_dict *root, char *key);
t_dict	*bst_copy(t_dict *root);
size_t	bst_size(t_dict *root);
void	free_node(t_dict *node);
void	free_branch(t_dict *root);

#endif