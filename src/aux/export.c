/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 00:08:41 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/06 18:28:23 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	export_var(char *var_name)
{
	char	**new_env;
	int		i;

	i = 0;
	while (g_vars->env[i] != NULL)
			i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (g_vars->env[++i] != NULL)
	{
		if (g_vars->env[i] != NULL)
			new_env[i] = ft_strdup(g_vars->env[i]);
	}
	new_env[i] = ft_strdup(var_name);
	new_env[++i] = NULL;
	if (g_vars->n_env == 1)
		ft_split_free(g_vars->env);
	g_vars->n_env = 1;
	g_vars->env = new_env;
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
		if (ft_isdigit(var_name[0]) == 0 && var_name[0] != '$')
		{
			check_variable_exists(var);
			free(var);
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
		get_var_name(aux->val);
		aux = aux->next;
	}
}

void	export_env(t_input *src)
{
	int		i;
	char	**new_env;

	i = -1;
	while (g_vars->env[++i] != NULL)
		;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (g_vars->env[++i] != NULL)
			new_env[i] = g_vars->env[i];
	new_env[i] = NULL;
	order_env(new_env);
	write_to_pipe(new_env, src);
	i = -1;
	while (new_env[++i] != NULL)
		free(new_env[i]);
	free(new_env);
}
