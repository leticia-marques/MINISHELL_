/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque < lemarque@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 00:39:57 by lemarque          #+#    #+#             */
/*   Updated: 2022/03/18 00:39:57 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	redirect_error(char *symbol)
{
	if (symbol[0] == '\0')
		printf("bash: syntax error near unexpected token 'newline'\n");
	else
		printf("bash: syntax error near unexpected token `%s`\n", symbol);
	g_vars->exit_code = 2;
}

void	error(int code, char *cmd_path, char **command)
{
	if (code == 1)
	{
		perror("error:");
		free_cmd(command);
		free(cmd_path);
	}
}

void	error_infile(t_node **cmd, int code)
{
	if (code == 2)
	{
		free_node(cmd);
		perror("error:");
	}
}

void	command_not_found(char *cmd, char **splited_path)
{
	printf("%s:command not found\n", cmd);
	if (splited_path)
		ft_split_free(splited_path);
	g_vars->exit_code = 127;
}
