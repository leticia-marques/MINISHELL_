/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:14:48 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/28 04:38:42 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	first_outfile(t_node **cmd, t_node	**aux)
{
	t_node	*redirect;
	t_node	*file;

	if ((*aux)->next->next)
	{
		if (!ft_strcmp((*aux)->next->val.str, ">"))
			(*cmd)->outfile = open((*aux)->next->next->val.str, O_WRONLY \
			| O_CREAT | O_TRUNC, 0777);
		else
			(*cmd)->outfile = open((*aux)->next->next->val.str, O_WRONLY \
			| O_CREAT | O_APPEND, 0777);
		if ((*cmd)->outfile == -1)
			error_infile(cmd, 2);
		redirect = (*aux)->next;
		file = (*aux)->next->next;
		(*aux)->next = (*aux)->next->next->next;
		free_node(redirect);
		free_node(file);
	}
}

static void	multiple_outfiles(t_node **cmd, t_node	**aux)
{
	t_node	*redirect;
	t_node	*file;

	if ((*aux)->next)
	{
		if ((*cmd)->outfile != -1)
			close((*cmd)->outfile);
		if (!ft_strcmp((*aux)->val.str, ">"))
			(*cmd)->outfile = open((*aux)->next->val.str, O_WRONLY \
			| O_CREAT | O_TRUNC, 0777);
		else
			(*cmd)->outfile = open((*aux)->next->val.str, O_WRONLY \
			| O_CREAT | O_APPEND, 0777);
		if ((*cmd)->outfile == -1)
			error_infile(cmd, 2);
		redirect = (*aux);
		file = (*aux)->next;
		*aux = (*aux)->next->next;
		free_node(redirect);
		free_node(file);
	}
}

static void	has_outfile(t_node **cmd)
{
	t_node	*aux;

	aux = (*cmd)->first_arg;
	while (aux)
	{
		if (!aux->next)
			break ;
		else if (!ft_strcmp(aux->next->val.str, ">") || \
				!ft_strcmp(aux->next->val.str, ">>"))
			first_outfile(cmd, &aux);
		else if (!ft_strcmp(aux->val.str, ">") || \
				!ft_strcmp(aux->val.str, ">>"))
			multiple_outfiles(cmd, &aux);
		if (!aux)
			break ;
		else if (!ft_strcmp(aux->val.str, ">") || \
		!ft_strcmp(aux->val.str, ">>"))
			continue ;
		aux = aux->next;
	}
}

int	check_outfile(t_node **cmd)
{
	if (check_syntax_error(cmd) != 0)
	{
		has_outfile(cmd);
		if ((*cmd)->outfile != -1)
		{
			dup2((*cmd)->outfile, STDOUT_FILENO);
			close((*cmd)->outfile);
		}
		return (1);
	}
	return (0);
}
