/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 00:52:21 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/03 23:39:57 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	child_process(t_node *cmd, char **command, char **envp, int fd[2])
{
	if (cmd->outfile == -1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (execve(cmd->cmd_path, command, envp) == -1)
		error(1, cmd->cmd_path, command);
}

static void	parent_process(t_node *cmd, char **command, int fd[2])
{
	waitpid(g_vars->pid, &g_vars->w_status, 0);
	if (!WIFSIGNALED(g_vars->w_status))
		g_vars->exit_code = WEXITSTATUS(g_vars->w_status);
	else
		g_vars->exit_code = g_vars->w_status + 128;
	if (cmd->outfile != -1)
		close(cmd->outfile);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_split_free(command);
	free(cmd->cmd_path);
}

void	exec_cmd(t_node *cmd, char **command, char **envp, int *fd)
{
	cmd->cmd_path = find_path(command[0]);
	if (!cmd->cmd_path)
	{
		free_cmd(command);
		return ;
	}
	if (pipe(fd) == -1)
		error(1, cmd->cmd_path, command);
	g_vars->pid = fork();
	if (g_vars->pid == -1)
		error(1, cmd->cmd_path, command);
	else if (g_vars->pid == 0)
		child_process(cmd, command, envp, fd);
	else
		parent_process(cmd, command, fd);
}
