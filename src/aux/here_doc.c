/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:05:40 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/06 22:49:03 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	child_process_aux(char *delimiter, t_node **cmd, char *line, int n1)
{
	if (n1 == 1)
	{
		printf("minishell: warning: here-document delimited ");
		printf("by end-of-file (wanted `%s`)\n", delimiter);
	}
	if (n1 == 2)
	{
		ft_putstr_fd(line, (*cmd)->outfile);
		ft_putchar_fd('\n', (*cmd)->outfile);
	}
}

static void	child_process_aux2(char *line, int fd[2])
{
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
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
				child_process_aux2(line, fd);
			else
				child_process_aux(delimiter, cmd, line, 2);
		}
		else
		{
			if (line == NULL)
				child_process_aux(delimiter, cmd, line, 1);
			break ;
		}
	}
	if (line)
		free(line);
	g_vars->exit_code = 1;
}

static void	here_doc_aux(t_token_holder *holder, t_node **cmd, t_input *s)
{
	free_vars_and_holder(holder);
	free_node(cmd);
	free(s->line);
}

int	here_doc(char *delimiter, t_token_holder *holder, t_node **cmd, t_input *s)
{
	int	fd[2];

	signal(SIGINT, SIG_IGN);
	if (pipe(fd) == 1)
	{
		perror("Error:");
		return (errno);
	}
	holder->here_doc_fork = fork();
	if (holder->here_doc_fork == 0)
	{
		child_process(fd, delimiter, cmd);
		close(fd[1]);
		dup2(fd[0], STDOUT_FILENO);
		close(fd[0]);
		here_doc_aux(holder, cmd, s);
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
