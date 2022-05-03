/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:05:40 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/03 16:35:14 by lemarque         ###   ########.fr       */
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

static void	child_process(int fd[2], char *delimiter, t_node **cmd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		signal(SIGINT, here_doc_sig);
		line = readline("> ");
		if (line != NULL && (ft_strcmp(line, delimiter) != 0))
		{
			if ((*cmd)->outfile == -1)
			{
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
			}
			else
			{
				ft_putstr_fd(line, (*cmd)->outfile);
				ft_putchar_fd('\n', (*cmd)->outfile);
			}
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

int	here_doc(char *delimiter, t_token_holder *holder, t_node **cmd, t_input *s)
{
	int	fd[2];
	int	i;

	signal(SIGINT, SIG_IGN);
	if (pipe(fd) == 1)
	{
		perror("Error:");
		return (errno);
	}
	i = fork();
	printf("Delimite:%s\n", delimiter);
	if (i == 0)
	{
		child_process(fd, delimiter, cmd);
		close(fd[1]);
		dup2(fd[0], STDOUT_FILENO);
		close(fd[0]);
		free_vars_and_holder(holder);
		// free_node(cmd);
		free(s->line);
		exit(1);
	}
	else
		wait(NULL);
	if ((*cmd)->outfile == -1)
		dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	return (0);
}
