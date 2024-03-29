/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_garbage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:20:54 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 17:50:33 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_garbage_add(t_garbage *garbage)
{
	if (garbage && garbage->split_pipe)
	{
		ft_free_tab(garbage->split_pipe);
		garbage->split_pipe = NULL;
	}
	if (garbage && garbage->split_lst)
	{
		free_split_elem(garbage->split_lst);
		garbage->split_lst = NULL;
	}
}

void	free_garbage(t_garbage *garbage)
{
	free_garbage_add(garbage);
	if (garbage && garbage->maillons)
	{
		free_maillons(garbage->maillons);
		garbage->maillons = NULL;
	}
	if (garbage && garbage->pipes)
	{
		free_all_pipes(garbage->pipes->len, garbage->pipes);
		garbage->pipes = NULL;
	}
	if (garbage && garbage->line)
	{
		free(garbage->line);
		garbage->line = NULL;
	}
}

void	free_garbage_exit(t_garbage *garbage, int exit_code)
{
	free_garbage_add(garbage);
	if (garbage && garbage->maillons)
	{
		free_maillons(garbage->maillons);
		garbage->maillons = NULL;
	}
	if (garbage && garbage->pipes)
	{
		free_all_pipes(garbage->pipes->len, garbage->pipes);
		garbage->pipes = NULL;
	}
	if (garbage && garbage->line)
	{
		free(garbage->line);
		garbage->line = NULL;
	}
	exit(exit_code);
}

void	free_garbage_and_env(t_garbage *garbage)
{
	free_garbage_add(garbage);
	if (garbage && garbage->maillons)
	{
		free_maillons(garbage->maillons);
		garbage->maillons = NULL;
	}
	if (garbage && garbage->pipes)
	{
		free_all_pipes(garbage->pipes->len, garbage->pipes);
		garbage->pipes = NULL;
	}
	if (garbage && garbage->line)
	{
		free(garbage->line);
		garbage->line = NULL;
	}
	if (garbage && garbage->new_env)
	{
		ft_free_tab(garbage->new_env);
		garbage->new_env = NULL;
	}
}

void	free_garbage_env_exit(t_garbage *garbage, int exit_code)
{
	free_garbage_add(garbage);
	if (garbage && garbage->maillons)
	{
		free_maillons(garbage->maillons);
		garbage->maillons = NULL;
	}
	if (garbage && garbage->pipes)
	{
		free_all_pipes(garbage->pipes->len, garbage->pipes);
		garbage->pipes = NULL;
	}
	if (garbage && garbage->line)
	{
		free(garbage->line);
		garbage->line = NULL;
	}
	if (garbage && garbage->new_env)
	{
		ft_free_tab(garbage->new_env);
		garbage->new_env = NULL;
	}
	close (0);
	close (1);
	close (2);
	exit(exit_code);
}
