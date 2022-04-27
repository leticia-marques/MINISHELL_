/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:05:40 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/27 17:25:39 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	here_doc_sig(int sig)
{
	vars->exit_code = 130;
	(void)sig;
	write(1, "\n", 1);
	exit (130);
}

static void	child_process(int fd[2], char *delimiter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		signal(SIGINT, here_doc_sig);
		line = readline("> ");
		if (line != NULL && (ft_strcmp(line, delimiter) != 0))
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		else
		{
			if (line == NULL)
			{
				printf("minishell: warning: here-document delimited ");
				printf("by end-of-file (wanted `%s`)\n", delimiter);
			}
			break ;
		}
	}
	if (line)
		free(line);
	vars->exit_code = 1;
}
int	here_doc(char *delimiter)
{
	int		fd[2];
	int i;

	signal(SIGINT, SIG_IGN);
	if (pipe(fd) == 1)
	{
		perror("Error:");
		return (errno);
	}
	i = fork();
	// dup2(vars->save_stdin, 0);
	// dup2(vars->save_stdout, 1);
	if (i == 0)
	{
		child_process(fd, delimiter);
		close(fd[1]);
		dup2(fd[0], STDOUT_FILENO);
		close(fd[0]);
		exit(1);
	}
	else
		wait(NULL);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	return (0);
}
