/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:01:56 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/25 11:01:58 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	ft_dup2(int fd1, int fd2)
{
	int	i;

	i = dup2(fd1, fd2);
	if (i < 0)
	{
		perror("dup2");
		exit(0);
	}
}

int	append_redirection(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
		perror(file);
		return (1);
	}
	ft_dup2 (fd, 1);
	close (fd);
	return (0);
}

int	output_redirection(char *file)
{
	int	fd;

	fd = open (file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
		if (errno != 14) // replace this,
			perror (file);
		return (1);
	}
	ft_dup2 (fd, 1);
	close (fd);
	return (0);
}

int	input_redirection(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return (1);
	}
	ft_dup2 (fd, 0);
	close (fd);
	return (0);
}

/* O-> output, A-> append, I-> input, H-> heredoc */

int	mini_redirect(t_list *redir)
{
	t_redir	*redirection;

	while (redir != NULL)
	{
		redirection = redir->content;
		if (redirection->type == 'O' && output_redirection(redirection->file))
			return (1);
		if (redirection->type == 'A' && append_redirection(redirection->file))
			return (1);
		if (redirection->type == 'I' && input_redirection(redirection->file))
			return (1);
		if (redirection->type == 'H' && input_redirection("/tmp/file1")) //check this
			return (1);
		redir = redir->next;
	}
	return (0);
}