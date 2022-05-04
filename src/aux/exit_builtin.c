/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:11:46 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/03 20:37:37 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_exit_expansion(t_node **cmd)
{
	t_node	*aux;
	int		exit_code_size;
	char	*str;

	str = ft_itoa(vars->exit_code);
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
	vars->exit_code = ft_atoi(cmd->first_arg->next->val);
	free_node(&cmd);
	printf("exit\n");
	exit(vars->exit_code);
}
