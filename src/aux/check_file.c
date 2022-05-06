/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:14:48 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/05 23:35:45 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// static void	first_outfile(t_node **cmd, t_node	**aux)
// {
// 	t_node	*redirect;
// 	t_node	*file;

// 	if ((*aux)->next->next)
// 	{
// 		if (!ft_strcmp((*aux)->next->val, ">"))
// 			(*cmd)->outfile = open((*aux)->next->next->val, O_WRONLY
// 			| O_CREAT | O_TRUNC, 0777);
// 		else
// 			(*cmd)->outfile = open((*aux)->next->next->val, O_WRONLY
// 			| O_CREAT | O_APPEND, 0777);
// 		if ((*cmd)->outfile == -1)
// 			error_infile(cmd, 2);
// 		redirect = (*aux)->next;
// 		file = (*aux)->next->next;
// 		(*aux)->next = (*aux)->next->next->next;
// 		free_node(&redirect);
// 		free_node(&file);
// 		// (*cmd)->args-= 2;
// 	}
// }

// static void	multiple_outfiles(t_node **cmd, t_node	**aux)
// {
// 	t_node	*redirect;
// 	t_node	*file;

// 	if ((*aux)->next)
// 	{
// 		if ((*cmd)->outfile != -1)
// 			close((*cmd)->outfile);
// 		if (!ft_strcmp((*aux)->val, ">"))
// 			(*cmd)->outfile = open((*aux)->next->val, O_WRONLY
// 			| O_CREAT | O_TRUNC, 0777);
// 		else
// 			(*cmd)->outfile = open((*aux)->next->val, O_WRONLY
// 			| O_CREAT | O_APPEND, 0777);
// 		if ((*cmd)->outfile == -1)
// 			error_infile(cmd, 2);
// 		redirect = (*aux);
// 		file = (*aux)->next;
// 		*aux = (*aux)->next->next;
// 		free_node(&redirect);
// 		free_node(&file);
// 		// (*cmd)->args-= 2;
// 	}
// }

// static void	has_outfile(t_node **cmd)
// {
// 	t_node	*aux;

// 	aux = (*cmd)->first_arg;
// 	while (aux)
// 	{
// 		if (!aux->next)
// 			break ;
// 		else if (!ft_strcmp(aux->next->val, ">") ||
// 				!ft_strcmp(aux->next->val, ">>"))
// 			first_outfile(cmd, &aux);
// 		else if (!ft_strcmp(aux->val, ">") ||
// 				!ft_strcmp(aux->val, ">>"))
// 			multiple_outfiles(cmd, &aux);
// 		if (!aux)
// 			break ;
// 		else if (!ft_strcmp(aux->val, ">") ||
// 		!ft_strcmp(aux->val, ">>"))
// 			continue ;
// 		aux = aux->next;
// 	}
// 	aux = (*cmd)->first_arg;
// 	while(aux)
// 	{
// 		printf("Aux:%s\n", aux->val);
// 		aux =aux->next;
// 	}
// }

static	void	open_file(t_node **aux, t_node **cmd)
{
	t_node	*infile;
	t_node	*redirect;
	t_node	*prev;

	if ((*cmd)->outfile != -1)
		close((*cmd)->outfile);
	if (!ft_strcmp((*aux)->val, ">"))
		(*cmd)->outfile = open((*aux)->next->val, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		(*cmd)->outfile = open((*aux)->next->val, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if ((*cmd)->outfile == -1)
		error_infile(cmd, 2);
	prev = (*aux)->prev;
	infile = (*aux)->next;
	redirect = (*aux);
	*aux = (*aux)->next->next;
	prev->next = *aux;
	if ((*aux))
		(*aux)->prev = prev;
	free_node(&infile);
	free_node(&redirect);
}

static void	has_outfile(t_node **cmd)
{
	t_node	*aux;

	aux = (*cmd)->first_arg;
	while (aux)
	{
		if (!ft_strcmp(aux->val, ">") || !ft_strcmp(aux->val, ">>"))
			open_file(&aux, cmd);
		if (aux)
		{
			if (!ft_strcmp(aux->val, ">") || !ft_strcmp(aux->val, ">>"))
				continue ;
		}
		if (aux)
		{
			if (aux->next)
				aux = aux->next;
		}
	}
}

int	check_outfile(t_node **cmd, int i, t_input *src)
{
	if (check_syntax_error(cmd) != 0)
	{
		has_outfile(cmd);
		if ((*cmd)->outfile != -1 && i != 0)
		{
			dup2((*cmd)->outfile, STDOUT_FILENO);
			close((*cmd)->outfile);
		}
		if (ft_strcmp((*cmd)->first_arg->val, "echo") == 0)
			return (check_echo(cmd, &src));
		return (1);
	}
	return (0);
}
