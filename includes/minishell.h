/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 18:12:53 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/26 17:19:52 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <errno.h>
# include <termios.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

# include "parse.h"
# include "exec.h"

typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	t_list	*redir;
}	t_cmd;

typedef struct s_redir
{
	char	type;
	char	*file;
}	t_redir;

typedef struct s_var
{
	int						i;
	char					*result;
}	t_var;

typedef struct s_parse
{
	int						arg_num;
	int						i;
	int						ambiguous;
	int						ret_value;
	char					**extra_args;
	int						outside_quote;
	t_var					var;
}	t_parse;

int		g_exit_status;

void	free_env_list(t_list *env);

int		put_err(char *err_msg);
int		check_quote(char c, int quote);
int		redir_error(char *str);
int		syntax_validation(char *s);

// signals
void	handle_signal(int signal);

// utils
int		ft_strcasecmp(const char *s1, const char *s2);
void	ft_execve(char *path, char **args, char **tab);
void	ft_dup2(int fd1, int fd2);
void	ft_swap(char **str1, char **str2);

/* Preparing environment variables */
void	reset_env_node(t_env *new);
void	parse_env(char **envp);

#endif
