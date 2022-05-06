/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:11:46 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/04 18:12:29 by lemarque         ###   ########.fr       */
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

int	exit_builtin(t_node *cmd, t_token_holder *holder, t_input *src)
{
	int	i;
	int	exit_code;

	i = -1;
	if (cmd->args > 2)
	{
		g_vars->exit_code = 127;
		printf("bash: exit: too many arguments");
		return (0);
	}
	while (cmd->first_arg->next->val[++i])
	{
		if (ft_isdigit(cmd->first_arg->next->val[i]) == 0)
		{
			printf("exit\n");
			printf("bash: exit: %s: ", cmd->first_arg->next->val);
			printf("numeric argument required\n");
			exit(2);
		}
	}
	g_vars->exit_code = ft_atoi(cmd->first_arg->next->val);
	exit_code = g_vars->exit_code;
	free_node(&cmd);
	free_vars_and_holder(holder);
	free(src->line);
	printf("exit\n");
	exit(exit_code);
}
