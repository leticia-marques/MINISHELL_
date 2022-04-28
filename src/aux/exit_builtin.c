/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:11:46 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/28 04:55:52 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	exit_builtin(t_node *cmd)
{
	int	i;

	i = -1;
	if (cmd->args > 2)
	{
		vars->exit_code = 127;
		printf("bash: exit: too many arguments");
		return (0);
	}
	while (cmd->first_arg->next->val.str[++i])
	{
		if (ft_isdigit(cmd->first_arg->next->val.str[i]) == 0)
		{
			printf("exit\n");
			printf("bash: exit: %s: ", cmd->first_arg->next->val.str);
			printf("numeric argument required\n");
			exit(2);
		}
	}
	vars->exit_code = ft_atoi(cmd->first_arg->next->val.str);
	free_node(cmd);
	printf("exit\n");
	exit(vars->exit_code);
}
