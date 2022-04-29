/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:18:44 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/29 18:45:19 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	here_doc_call(t_node **cmd, t_token_holder *holder, t_input *src)
{
	if (check_syntax_error(cmd) != 0)
	{
		here_doc((*cmd)->first_arg->next->val.str, holder, cmd, src);
		check_outfile(cmd);
		if ((*cmd)->args > 2)
		{
			filter_cmd(cmd);
			return (1);
		}
	}
	return (0);
}

int	infile_outfile_call(t_node **cmd)
{
	(*cmd)->infile = open((*cmd)->first_arg->next->val.str, O_RDONLY, 666);
	if ((*cmd)->infile == -1)
		error_infile(cmd, 2);
	check_outfile(cmd);
	if ((*cmd)->args > 2)
	{
		dup2((*cmd)->infile, STDIN_FILENO);
		close((*cmd)->infile);
		filter_cmd(cmd);
		return (1);
	}
	return (0);
}
