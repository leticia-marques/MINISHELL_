/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:18:44 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/06 23:09:25 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	here_doc_call(t_node **cmd, t_token_holder *holder, t_input *src)
{
	t_node	*aux;

	aux = (*cmd)->first_arg;
	while (aux)
	{
		if (ft_strcmp(aux->val, "<<") == 0)
		{
			check_outfile(cmd, 1, src);
			here_doc(aux->next->val, holder, cmd, src);
			if (aux->prev != NULL && (*cmd)->outfile == -1)
			{
				filter_cmd_here_doc(cmd);
				return (1);
			}
			if ((*cmd)->args > 2 && (*cmd)->outfile == -1)
			{
				filter_cmd(cmd);
				return (1);
			}
		}
		aux = aux->next;
	}
	return (0);
}

int	infile_outfile_call(t_node **cmd, t_input *src)
{
	(*cmd)->infile = open((*cmd)->first_arg->next->val, O_RDONLY, 666);
	if ((*cmd)->infile == -1)
		error_infile(cmd, 2);
	check_outfile(cmd, 1, src);
	if ((*cmd)->args > 2)
	{
		dup2((*cmd)->infile, STDIN_FILENO);
		close((*cmd)->infile);
		filter_cmd(cmd);
		return (1);
	}
	return (0);
}
