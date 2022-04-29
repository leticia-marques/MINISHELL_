/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:05:40 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/29 18:46:10 by jinacio-         ###   ########.fr       */
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

void	free_nodess(t_node **node)
{
	t_node	*aux;
	t_node	*tmp;

	if (!(*node))
		return ;
	aux = (*node)->first_arg;
	while (aux)
	{
		tmp = aux->next;
		free_node(aux);
		aux = tmp;
	}
	if ((*node)->val.str)
		free((*node)->val.str);
	free((*node));
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
	if (i == 0)
	{
		child_process(fd, delimiter);
		close(fd[1]);
		dup2(fd[0], STDOUT_FILENO);
		close(fd[0]);
		free_vars_and_holder(holder);
		free_nodess(cmd);
		free(s->line);
		exit(1);
	}
	else
		wait(NULL);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	return (0);
}
