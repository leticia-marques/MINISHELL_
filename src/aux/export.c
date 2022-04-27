/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 00:08:41 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/16 18:23:04 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	export_var(char *var_name)
{
	char	**new_env;
	int		i;

	i = 0;
	while (vars->env[i] != NULL)
				i++;
	new_env = malloc(sizeof(char *) * i + 2);
	i = -1;
	while (vars->env[++i] != NULL)
	{
		if (vars->env[i] != NULL)
			new_env[i] = ft_strdup(vars->env[i]);
	}
	new_env[i] = strdup(var_name);
	new_env[++i] = NULL;
	vars->env = new_env;
}

static void	get_var_name(char *var_name)
{
	char	*var;
	int		i;

	i = 0;
	if (ft_strchr(var_name, '='))
	{
		while (var_name[i] != '\0' && var_name[i] != '=')
		i++;
		var = ft_substr(var_name, 0, i);
		if (!var)
			return ;
		if (ft_isdigit(var_name[0]) == 0)
		{
			check_variable_exists(var);
			export_var(var_name);
			return ;
		}
		printf("export: not an identifier: %s\n", var);
	}
}

void	export(t_node **cmd)
{
	t_node	*aux;

	aux = (*cmd)->first_arg;
	while (aux)
	{
		get_var_name(aux->val.str);
		aux = aux->next;
	}
}

void	export_env()
{
	int		i;
	char	**new_env;

	i = -1;
	while (vars->env[++i] != NULL)
		;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (vars->env[++i] != NULL)
			new_env[i] = vars->env[i];
	new_env[i] = NULL;
	order_env(new_env);
	write_to_pipe(new_env);
	i = -1;
	while (new_env[++i] != NULL)
		free(new_env[i]);
	free(new_env);
}
