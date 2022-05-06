/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:01:54 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/05 14:54:32 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	extract_loop(t_node *arg, char **command)
{
	int	i;

	i = -1;
	while (arg)
	{
		if (!arg->val)
		{
			while (arg && !arg->val)
				arg = arg->next;
			if (!arg)
				break ;
			else if (arg->val)
				continue ;
		}
		command[++i] = ft_strdup(arg->val);
		if (!command[i])
		{
			free_cmd(command);
			return (0);
		}
		arg = arg->next;
	}
	return (i);
}

char	**extract_cmd(t_node *cmd)
{
	char	**command;
	int		i;
	t_node	*arg;

	arg = cmd->first_arg;
	i = 0;
	command = malloc(sizeof(char *) * (cmd->args + 1));
	if (!command)
		return (NULL);
	i = extract_loop(arg, command);
	command[++i] = NULL;
	return (command);
}

void	check_cmd(t_node *cmd, char **envp)
{
	char	**command;
	int		fd[2];

	command = extract_cmd(cmd);
	if (!command)
		return ;
	exec_cmd(cmd, command, envp, fd);
}
