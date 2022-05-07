/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 20:31:03 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/06 19:44:20 by lemarque         ###   ########.fr       */
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
	while (g_vars->env[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return ;
	i = -1;
	while (g_vars->env[++i] != NULL)
	{
		if (g_vars->env[i] != NULL && \
			ft_strncmp(var, g_vars->env[i], ft_strlen(var)) != 0)
				new_env[++j] = ft_strdup(g_vars->env[i]);
	}
	new_env[++j] = NULL;
	if (g_vars->n_env == 1)
		ft_split_free(g_vars->env);
	g_vars->n_env = 1;
	g_vars->env = new_env;
}

void	check_variable_exists(char *var)
{
	int		i;

	i = -1;
	if (var[0] == '$')
		var++;
	while (g_vars->env[++i] != NULL)
	{
		if (ft_strncmp(var, g_vars->env[i], ft_strlen(var)) == 0)
		{
			unset_var(var);
			break ;
		}
	}
}

void	unset(t_node **cmd)
{
	t_node	*aux;

	g_vars->exit_code = 0;
	aux = (*cmd)->first_arg;
	while (aux)
	{
		check_variable_exists(aux->val);
		aux = aux->next;
	}
}
