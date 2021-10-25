/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_validation.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 13:44:35 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/25 15:44:15 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	quote_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] != '"')
				return (put_err("minishell: unclosed double quote"));
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] != '\'')
				return (put_err("minishell: unclosed single quote"));
		}
		i++;
	}
	return (0);
}

static int	pipe_quote_error(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = check_quote(str[i], quote);
			i++;
		}
		if (str[i] == '|' && !quote)
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '|')
				return (put_err
					("minishell: syntax error near unexpected token `|'"));
		}
		i++;
	}
	return (0);
}

static int	semi_pipe_error(char *str)
{
	if (str == NULL)
		return (0);
	if (str[0] == ';')
	{
		if (str[1] == ';')
			return (put_err
				("minishell: syntax error near unexpected token `;;'"));
		else
			return (put_err
				("minishell: syntax error near unexpected token `;'"));
	}
	else if (str[0] == '|')
	{
		if (str[1] == '|')
			return (put_err
				("minishell: syntax error near unexpected token `||'"));
		else
			return (put_err
				("minishell: syntax error near unexpected token `|'"));
	}
	if (pipe_quote_error(str))
		return (1);
	return (0);
}

int	syntax_validation(char *s)
{
	char	*str;

	str = ft_strtrim(s, " ");
	if (semi_pipe_error(str) || quote_error(str) || redir_error(str))
	{
		free(str);
		return (1);
	}
	if (str[ft_strlen(str) - 1] == '|')
	{
		free(str);
		return (put_err
			("minishell: syntax error near unexpected token `newline'"));
	}
	free(str);
	return (0);
}
