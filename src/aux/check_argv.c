/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:56:55 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/09 22:46:12 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	check_builtin(t_node **cmd, t_input *src, t_token_holder *holder)
{
	if (ft_strcmp((*cmd)->first_arg->val, "export") == 0)
	{
		g_vars->exit_code = 0;
		if (src->position >= src->line_size && (*cmd)->first_arg->next != NULL)
			export(cmd);
		else
			export_env(src);
		return (0);
	}
	else if (ft_strcmp((*cmd)->first_arg->val, "unset") == 0)
	{
		if (src->position >= src->line_size && (*cmd)->first_arg->next != NULL)
			unset(cmd);
		return (0);
	}
	else if (ft_strcmp((*cmd)->first_arg->val, "cd") == 0)
		return (cd(*cmd));
	else if (ft_strcmp((*cmd)->first_arg->val, "exit") == 0)
		return (exit_builtin(*cmd, holder, src));
	else if (ft_strcmp((*cmd)->first_arg->val, "echo") == 0)
		return (check_echo(cmd, &src));
	return (1);
}

static void	init_cmd_fd(t_node **cmd)
{
	(*cmd)->infile = -1;
	(*cmd)->outfile = -1;
}

static int	has_redirection(t_node **cmd)
{
	t_node	*aux;

	aux = (*cmd)->first_arg;
	while (aux)
	{
		if (ft_strchr(aux->val, '<') || ft_strchr(aux->val, '>'))
			return (0);
		aux = aux->next;
	}
	return (1);
}

static int	check_here_doc(t_node **cmd)
{
	t_node	*aux;

	aux = (*cmd)->first_arg;
	while (aux)
	{
		if (ft_strcmp(aux->val, "<<") == 0)
			return (0);
		aux = aux->next;
	}
	return (1);
}

int	check_argv(t_node **cmd, t_input *src, t_token_holder *holder)
{
	int		i;
	char	*str;

	str = (*cmd)->first_arg->val;
	i = -1;
	init_cmd_fd(cmd);
	if (!(*cmd)->first_arg)
		return (0);
	else if (check_here_doc(cmd) == 0 && ft_strcmp(str, "echo") != 0)
		i = here_doc_call(cmd, holder, src);
	else if (ft_strncmp(str, "<", 1) == 0)
		i = infile_outfile_call(cmd, src);
	else if (has_redirection(cmd) == 0)
		i = check_outfile(cmd, 1, src);
	else
	{
		check_exit_expansion(cmd);
		i = check_builtin(cmd, src, holder);
	}
	if (i != -1)
		return (i);
	return (1);
}
