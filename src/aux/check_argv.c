/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:56:55 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/29 18:44:52 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


static int	check_builtin(t_node **cmd, t_input *src)
{
	if (ft_strcmp((*cmd)->first_arg->val.str, "export") == 0)
	{
		vars->exit_code = 0;
		if (src->position >= src->line_size && (*cmd)->first_arg->next != NULL)
			export(cmd);
		else
			export_env(src);
		return (0);
	}
	else if (ft_strcmp((*cmd)->first_arg->val.str, "unset") == 0)
	{
		if (src->position >= src->line_size && (*cmd)->first_arg->next != NULL)
			unset(cmd);
		return (0);
	}
	else if (ft_strcmp((*cmd)->first_arg->val.str, "cd") == 0)
		return (cd(*cmd));
	else if (ft_strcmp((*cmd)->first_arg->val.str, "exit") == 0)
		exit_builtin(*cmd);
	else if (ft_strcmp((*cmd)->first_arg->val.str, "echo") == 0)
		return (check_echo(cmd));
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

	while(aux)
	{
		if (ft_strchr(aux->val.str, '<') || ft_strchr(aux->val.str, '>'))
			return (0);
		aux = aux->next;
	}
	return (1);
}
int	check_argv(t_node **cmd, t_input *src, t_token_holder *holder)
{
	int		i;
	char	*str;

	str = (*cmd)->first_arg->val.str;
	i = -1;
	init_cmd_fd(cmd);
	if (!(*cmd)->first_arg)
		return (0);
	else if (ft_strncmp(str, "<<", 2) == 0)
		i = here_doc_call(cmd, holder, src);
	else if (ft_strncmp(str, "<", 1) == 0)
		i = infile_outfile_call(cmd);
	else if (has_redirection(cmd) == 0)
		i = check_outfile(cmd);
	else
	{
		check_exit_expansion(cmd);
		i = check_builtin(cmd, src);
	}
	if (i != -1)
		return (i);
	return (1);
}
