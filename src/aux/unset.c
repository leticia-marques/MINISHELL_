/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 20:31:03 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/19 23:37:16 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	unset_var(char *var)
{
	int		i;
	int		j;
	char	**new_env;

	j = -1;
	i = 0;
	while (vars->env[i] != NULL)
		i++;
	new_env = (char **)malloc(sizeof(char *) * i);
	if (!new_env)
		return ;
	i = -1;
	while (vars->env[++i] != NULL)
	{
		if (vars->env[i] != NULL && \
			ft_strncmp(var, vars->env[i], ft_strlen(var)) != 0)
				new_env[++j] = ft_strdup(vars->env[i]);
	}
	new_env[j++] = NULL;
	vars->env = new_env;
}

void	check_variable_exists(char *var)
{
	int		i;

	i = -1;
	if (var[0] == '$')
		var++;
	while (vars->env[++i] != NULL)
	{
		if (ft_strncmp(var, vars->env[i], ft_strlen(var)) == 0)
		{
			unset_var(var);
			break ;
		}
	}
}

void	unset(t_node **cmd)
{
	t_node	*aux;

	vars->exit_code = 0;
	aux = (*cmd)->first_arg;
	while (aux)
	{
		check_variable_exists(aux->val.str);
		aux = aux->next;
	}

}
