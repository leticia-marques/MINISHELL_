/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 00:34:15 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/03 18:57:55 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_node	*new_node(void)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	node->first_arg = NULL;
	node->val = NULL;
	node->args = 0;
	node->cmd_path = NULL;
	return (node);
}

void	add_argument_node(t_node *cmd, t_node *arg)
{
	t_node	*next_arg;

	if (!cmd || !arg)
		return ;
	if (!cmd->first_arg)
		cmd->first_arg = arg;
	else
	{
		next_arg = cmd->first_arg;
		while (next_arg->next)
			next_arg = next_arg->next;
		next_arg->next = arg;
		arg->prev = next_arg;
	}
	cmd->args++;
}
