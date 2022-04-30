/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:13:41 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/29 21:27:37 by lemarque         ###   ########.fr       */
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

	vars->prompt = ft_strjoin(PURPLE, vars->user);
	aux = vars->prompt;
	vars->prompt = ft_strjoin(aux, "@");
	free(aux);
	aux = vars->prompt;
	vars->prompt = ft_strjoin(aux, vars->name);
	free(aux);
	aux = vars->prompt;
	vars->prompt = ft_strjoin(aux, WHITE);
	free(aux);
	aux = ft_strjoin(vars->prompt, ":");
	free(vars->prompt);
	vars->prompt = ft_strjoin(aux, BLUE);
	free(aux);
	aux = vars->prompt;
	vars->prompt = ft_strjoin(aux, vars->path);
	free(aux);
	aux = vars->prompt;
	vars->prompt = ft_strjoin(aux, WHITE);
	free(aux);
	aux = vars->prompt;
	vars->prompt = ft_strjoin(aux, "$ ");
	free(aux);
}

void	init_vars(char **envp)
{
	vars = (t_vars *)malloc(sizeof(t_vars));
	vars->save_stdin = dup(0);
	vars->save_stdout = dup(1);
	vars->user = getenv("USER");
	vars->name = getenv("HOSTNAME");
	if (vars->name == NULL)
		vars->name = getenv("NAME");
	vars->env = envp;
	vars->pid = 0;
	vars->exit_code = 0;
	getcwd(vars->old_dir, 1024);
	getcwd(vars->path, 1024);
	get_prompt();
	vars->count = 1;
}
