/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 03:21:46 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/27 18:02:15 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	free_node(t_node *node)
{
	t_node *aux;
    t_node *tmp;

    if (!node)
        return;
    aux = node->first_arg;
    while (aux)
    {
        tmp = aux->next;
        free_node(aux);
        aux = tmp;
    }
   	if (node->val.str)
      free(node->val.str);
    free(node);
}

void	free_token(t_token *token)
{
	if (token->text)
		free(token->text);
	free(token);
}

void	free_cmd(char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
}

void	free_vars_and_holder(t_token_holder *holder)
{
	if (vars->line != NULL)
		free(vars->line);
	if (vars->prompt != NULL)
		free(vars->prompt);
	if (holder->token_buf)
		free(holder->token_buf);
	free(vars);
}
