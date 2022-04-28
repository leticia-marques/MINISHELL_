/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:26:48 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/28 04:37:56 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	cd(t_node *cmd)
{
	char	*path;
	char	*old_cwd;

	vars->exit_code = 0;
	old_cwd = malloc(sizeof(char ) * ft_strlen(vars->old_dir) + 1);
	ft_strlcpy(old_cwd, vars->old_dir, ft_strlen(vars->old_dir) + 1);
	if (cmd->args == 1)
		path = getenv("HOME");
	else
		path = cmd->first_arg->next->val.str;
	if (ft_strcmp(path, "~") == 0)
		path = getenv("HOME");
	if (ft_strcmp(path, "-") == 0)
		path = old_cwd;
	getcwd(vars->old_dir, 1024);
	if (chdir(path) != 0)
	{
		vars->exit_code = 1;
		printf("cd: %s: no such file or directory\n", path);
		return (0);
	}
	getcwd(vars->path, 1024);
	get_prompt();
	free(old_cwd);
	return (0);
}
