/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:18:44 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/29 16:32:36 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	here_doc_call(t_node **cmd)
{
	if (check_syntax_error(cmd) != 0)
	{
		check_outfile(cmd, 0);
		here_doc((*cmd)->first_arg->next->val.str, cmd);
		if ((*cmd)->args > 2 && (*cmd)->outfile == -1)
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
	check_outfile(cmd, 1);
	if ((*cmd)->args > 2)
	{
		dup2((*cmd)->infile, STDIN_FILENO);
		close((*cmd)->infile);
		filter_cmd(cmd);
		return (1);
	}
	return (0);
}
