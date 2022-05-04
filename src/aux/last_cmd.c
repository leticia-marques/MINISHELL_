/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:17:06 by jinacio-          #+#    #+#             */
/*   Updated: 2022/05/03 23:43:36 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	signal_to_cat(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	return ;
}

static void	parent_process(char *cmd_path, char **command)
{
	waitpid(g_vars->pid, &g_vars->w_status, 0);
	if (!WIFSIGNALED(g_vars->w_status))
		g_vars->exit_code = WEXITSTATUS(g_vars->w_status);
	else
		g_vars->exit_code = g_vars->w_status + 128;
	ft_split_free(command);
	free(cmd_path);
}

void	exec_last_cmd(t_node *cmd, char **envp)
{
	char	*cmd_path;
	char	**command;

	signal(SIGINT, signal_to_cat);
	command = extract_cmd(cmd);
	if (!command)
		return ;
	cmd_path = find_path(command[0]);
	if (!cmd_path)
	{
		free_cmd(command);
		return ;
	}
	g_vars->pid = fork();
	if (g_vars->pid == -1)
		error(1, cmd_path, command);
	if (g_vars->pid == 0)
	{
		if (execve(cmd_path, command, envp) == -1)
			error(1, cmd_path, command);
	}
	else
		parent_process(cmd_path, command);
}
