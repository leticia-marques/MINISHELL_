/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 00:52:21 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/28 04:37:27 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	signal_to_cat(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	return ;
}

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
	waitpid(vars->pid, &vars->w_status, 0);
	if (!WIFSIGNALED(vars->w_status))
		vars->exit_code = WEXITSTATUS(vars->w_status);
	else
		vars->exit_code = vars->w_status + 128;
	if (cmd->outfile != -1)
		close(cmd->outfile);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_split_free(command);
	free(cmd->cmd_path);
	free_node(cmd);
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
	vars->pid = fork();
	if (vars->pid == -1)
		error(1, cmd->cmd_path, command);
	else if (vars->pid == 0)
		child_process(cmd, command, envp, fd);
	else
		parent_process(cmd, command, fd);
}
