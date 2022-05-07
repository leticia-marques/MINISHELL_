/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:13:41 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/06 18:21:29 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	init_end_token(t_token *end_token)
{
	end_token->text_size = 0;
	end_token->text = NULL;
}

void	init_holder(t_token_holder *holder)
{
	holder->buf_size = 1024;
	holder->token_buf = malloc(holder->buf_size);
	holder->buf_position = -1;
}

void	init_src(t_input *source, char *line)
{
	char	*formatted_line;

	formatted_line = format_line(line, ft_strlen(line));
	source->line = formatted_line;
	source->line_size = ft_strlen(formatted_line);
	source->position = -2;
}

void	get_prompt(void)
{
	char	*aux;

	g_vars->prompt = ft_strjoin(PURPLE, g_vars->user);
	aux = g_vars->prompt;
	g_vars->prompt = ft_strjoin(aux, "@");
	free(aux);
	aux = g_vars->prompt;
	g_vars->prompt = ft_strjoin(aux, g_vars->name);
	free(aux);
	aux = g_vars->prompt;
	g_vars->prompt = ft_strjoin(aux, WHITE);
	free(aux);
	aux = ft_strjoin(g_vars->prompt, ":");
	free(g_vars->prompt);
	g_vars->prompt = ft_strjoin(aux, BLUE);
	free(aux);
	aux = g_vars->prompt;
	g_vars->prompt = ft_strjoin(aux, g_vars->path);
	free(aux);
	aux = g_vars->prompt;
	g_vars->prompt = ft_strjoin(aux, WHITE);
	free(aux);
	aux = g_vars->prompt;
	g_vars->prompt = ft_strjoin(aux, "$ ");
	free(aux);
}

void	init_vars(char **envp)
{
	g_vars = (t_vars *)malloc(sizeof(t_vars));
	g_vars->save_stdin = dup(0);
	g_vars->save_stdout = dup(1);
	g_vars->user = getenv("USER");
	g_vars->name = getenv("HOSTNAME");
	if (g_vars->name == NULL)
		g_vars->name = getenv("NAME");
	g_vars->env = envp;
	g_vars->pid = 0;
	g_vars->exit_code = 0;
	getcwd(g_vars->old_dir, 1024);
	getcwd(g_vars->path, 1024);
	get_prompt();
	g_vars->n_env = 0;
}
