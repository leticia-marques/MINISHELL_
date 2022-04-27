/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:56:55 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/27 18:16:18 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	check_exit_expansion(t_node **cmd)
{
	t_node	*aux;
	int		exit_code_size;

	exit_code_size = ft_strlen(ft_itoa(vars->exit_code));
	aux = (*cmd)->first_arg;
	while (aux)
	{
		if (ft_strcmp(aux->val.str, "$?") == 0)
		{
			free(aux->val.str);
			aux->val.str = malloc(sizeof(char) * exit_code_size +1);
			ft_strlcpy(aux->val.str, ft_itoa(vars->exit_code),exit_code_size +1);
		}
		aux = aux->next;
	}
	return (1);
}

static int	check_builtin(t_node **cmd, t_input *src)
{
	if (ft_strcmp((*cmd)->first_arg->val.str, "export") == 0)
	{
		vars->exit_code = 0;
		if (src->position >= src->line_size && (*cmd)->first_arg->next != NULL)
			export(cmd);
		else
			export_env();
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

int	check_argv(t_node **cmd, t_input *src)
{
	int	i;
	char	*str;

	str = (*cmd)->first_arg->val.str;
	i = -1;
	init_cmd_fd(cmd);
	if (!(*cmd)->first_arg)
		return (0);
	else if (ft_strncmp(str, "<<", 2) == 0)
		i = here_doc_call(cmd);
	else if (ft_strncmp(str, "<", 1) == 0)
		i = infile_outfile_call(cmd);
	else if (ft_strchr(str, '<') == 0 || ft_strchr(str, '>') == 0)
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
