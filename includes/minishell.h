/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:49:55 by jinacio-          #+#    #+#             */
/*   Updated: 2022/05/03 21:53:32 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PURPLE "\001\e[0;35m\002"
# define WHITE "\001\e[0;37m\002"
# define BLUE "\001\e[0;34m\002"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"
# include <fcntl.h> //access
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
//vars
typedef struct s_vars
{
	char	path[1024];
	char	*line;
	char	*prompt;
	char	*user;
	char	*name;
	int		save_stdin;
	int		save_stdout;
	char	**env;
	int		count;
	int		w_status;
	int		exit_code;
	int		pid;
	char	old_dir[1024];
}			t_vars;

extern t_vars	*vars;

void	init_vars(char **envp);
//tokenizer structs
typedef struct s_input
{
	char	*line;
	long	line_size;
	long	position;
}				t_input;

typedef struct s_token
{
	struct s_input	*src;
	int				text_size;
	char			*text;
}				t_token;

typedef struct s_token_holder
{
	char	*token_buf;
	int		buf_size;
	int		buf_position;
	int		here_doc_fork;
}				t_token_holder;
///////////////////////////////////////

//node structs

typedef struct s_node
{
	char				*val;
	int					args;
	struct s_node		*first_arg;
	struct s_node		*next;
	struct s_node		*prev;
	char				*cmd_path;
	int					infile;
	int					outfile;
}				t_node;

typedef struct s_format
{
	int					old_needle;
	int					new_needle;
	char				*new;
}				t_format;

typedef struct s_filter
{
	t_node			*aux;
	char			*line;
	char			*tmp_line;
	t_input			src;
	t_token_holder	holder;
}				t_filter;

typedef struct s_parser
{
	t_node	*cmd;
	t_node	*word;
	t_token	end_token;
	t_token	*token;
}				t_parser;

//node functions
t_node	*new_node(void);
void	add_argument_node(t_node *cmd, t_node *arg);

//parser
t_node	*parser_command(t_input *src, t_token_holder *holder);
void	set_value_str(t_node *node, char *val);

//find path and exec_cmd
char	*find_path(char *cmd);
void	check_cmd(t_node *cmd, char **envp);
void	exec_last_cmd(t_node *cmd, char **envp);
char	**extract_cmd(t_node *cmd);
void	check_cmd(t_node *cmd, char **envp);
void	exec_cmd(t_node *cmd, char **command, char **envp, int *fd);

//tokenizer functions
void	go_back_a_char(t_input *src);
char	next_char(t_input *src);
char	peek_char(t_input *src);
void	skip_white_spaces(t_input *src);
void	fill_buffer(char c, t_token_holder *holder);
t_token	*create_token(char *str);
t_token	*tokenizer(t_input *src, t_token_holder *holder, t_token *end_token);
void	get_arguments(char *args);
void	init_end_token(t_token *end_token);
void	init_holder(t_token_holder *holder);
void	init_src(t_input *source, char *line);

//parse and exec
int		check_argv(t_node **cmd, t_input *src, t_token_holder *holder);
int		here_doc(char *delimiter, t_token_holder *holder,
			t_node **cmd, t_input *s);
int		check_outfile(t_node **cmd, int i);//opens fds
int		here_doc_call(t_node **cmd, t_token_holder *holder, t_input *src);
int		infile_outfile_call(t_node **cmd);
void	filter_cmd(t_node **cmd);
//void	var_expansion(t_node **cmd);
char	*format_line(char *old, int len);
void	copy_and_walk(char **new, char **old, int *new_needle, int *old_needle);
void	get_space(char **new, int new_needle, int old_needle, int len);
void	clear_quotes(t_format *data, char *old, int len, char quote);
void	expand_var(t_format *data, char *old, int len, char symbol);
void	get_space_and_clear_quotes(t_format *data, int len, char **old);
void	check_char(t_format *data, char *old, int len);
void	check_unset_export(t_format **data, char *old, int len);

//error
void	error(int code, char *cmd_path, char **command);
void	error_infile(t_node **cmd, int code);
void	command_not_found(char *cmd, char **splited_path);
void	redirect_error(char *symbol);
int		check_syntax_error(t_node **cmd);

//free
void	free_token(t_token *token);
void	free_node(t_node **node);
void	free_cmd(char **command);
void	free_vars_and_holder(t_token_holder *holder);

//signal
void	signal_treatment(void);
void	signal_aborted(int sig);
void	here_doc_sig(int sig);

//read_infile
void	read_infile(void);

//builtins
void	export(t_node **cmd);
void	check_variable_exists(char *var);
void	export_env(t_input *src);
void	order_env(char **new_env);
void	write_to_pipe(char **new_env, t_input *src);
void	unset(t_node **cmd);
int		cd(t_node *cmd);
int		exit_builtin(t_node *cmd);
int		check_echo(t_node **cmd);
int		check_exit_expansion(t_node **cmd);
void	get_prompt(void);
#endif
