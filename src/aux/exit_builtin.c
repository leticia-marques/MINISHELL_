/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:11:46 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/09 22:49:01 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_exit_expansion(t_node **cmd)
{
	t_node	*aux;
	int		exit_code_size;
	char	*str;

	str = ft_itoa(g_vars->exit_code);
	exit_code_size = ft_strlen(str);
	aux = (*cmd)->first_arg;
	while (aux)
	{
		if (ft_strcmp(aux->val, "$?") == 0)
		{
			free(aux->val);
			aux->val = malloc(sizeof(char) * exit_code_size +1);
			ft_strlcpy(aux->val, str, exit_code_size + 1);
		}
		aux = aux->next;
	}
	free(str);
	return (1);
}

static void	exit_builtin_loop(t_node *cmd, t_token_holder *holder, t_input *src)
{
	int	i;

	i = -1;
	while (cmd->first_arg->next->val[++i])
	{
		if (ft_isdigit(cmd->first_arg->next->val[i]) == 0)
		{
			printf("exit\n");
			printf("bash: exit: %s: ", cmd->first_arg->next->val);
			printf("numeric argument required\n");
			free_node(&cmd);
			free_vars_and_holder(holder);
			free(src->line);
			exit(2);
		}
	}
}

int	exit_builtin(t_node *cmd, t_token_holder *holder, t_input *src)
{
	int	exit_code;

	exit_builtin_loop(cmd, holder, src);
	if (cmd->args > 2)
	{
		g_vars->exit_code = 127;
		printf("bash: exit: too many arguments\n");
		return (0);
	}
	
	g_vars->exit_code = ft_atoi(cmd->first_arg->next->val);
	exit_code = g_vars->exit_code;
	free_node(&cmd);
	free_vars_and_holder(holder);
	free(src->line);
	printf("exit\n");
	exit(exit_code);
}
