/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:26:48 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/03 23:42:20 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	cd(t_node *cmd)
{
	char	*path;
	char	*old_cwd;

	g_vars->exit_code = 0;
	old_cwd = malloc(sizeof(char ) * ft_strlen(g_vars->old_dir) + 1);
	ft_strlcpy(old_cwd, g_vars->old_dir, ft_strlen(g_vars->old_dir) + 1);
	if (cmd->args == 1)
		path = getenv("HOME");
	else
		path = cmd->first_arg->next->val;
	if (ft_strcmp(path, "~") == 0)
		path = getenv("HOME");
	if (ft_strcmp(path, "-") == 0)
		path = old_cwd;
	getcwd(g_vars->old_dir, 1024);
	if (chdir(path) != 0)
	{
		g_vars->exit_code = 1;
		printf("cd: %s: no such file or directory\n", path);
		return (0);
	}
	getcwd(g_vars->path, 1024);
	get_prompt();
	free(old_cwd);
	return (0);
}
