/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:44:00 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/20 17:44:05 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_pipes(int argc, t_pipes *pipes)
{
	int	i;

	i = 0;
	while (i < (argc * 2))
	{
		if (pipes && pipes->pipe[i] != -1)
		{
			close(pipes->pipe[i]);
			pipes->pipe[i] = -1;
		}
		i++;
	}
	if (pipes && pipes->pipe)
	{
		free(pipes->pipe);
		pipes->pipe = NULL;
	}
	if (pipes)
		free(pipes);
	pipes = NULL;
}

void	create_pipe(int *pipes, int i)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
	pipes[i] = pipe_fd[0];
	pipes[i + 1] = pipe_fd[1];
}

int	*create_pipes(int len)
{
	int	*pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * (len * 2));
	while (i < len * 2)
	{
		create_pipe(pipes, i);
		if (!pipes[i] || !pipes[i + 1])
			return (NULL);
		i = i + 2;
	}
	i = 0;
	return (pipes);
}

/*
* erreur ligne 65 free avant de exit
*/

t_pipes	*create_all_pipes(int len)
{
	t_pipes	*pipes;

	pipes = malloc(sizeof(t_pipes));
	pipes->pipe = create_pipes(len);
	pipes->len = len;
	if (!pipes || !pipes->pipe)
	{
		free_all_pipes(len * 2, pipes);
		unlink("here_doc");
		exit (1);
	}
	return (pipes);
}
