/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:29:01 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/22 17:53:16 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code[2];

static void	first_if(char **line, t_garbage *garbage)
{
	g_exit_code[1] = 0;
	setup_signal_handlers();
	(*line) = rl_gets();
	if ((*line) && (*line)[0] == '\0')
		g_exit_code[0] = 0;
	if ((*line) == NULL && g_exit_code[1] != 8)
	{
		s_fd("exit\n", 2);
		free_garbage_env_exit(garbage, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_garbage	garbage;

	if (!isatty(0))
		return (s_fd("Error: Invalid STDIN\n", 2), 0);
	initialize_garbage(&garbage, argc, argv);
	garbage.new_env = my_env(env, &garbage);
	while (1)
	{
		first_if(&line, &garbage);
		if (parse(line) == 0)
		{
			garbage.line = delete_dollar(line, garbage.new_env, 0);
			garbage.line = replace_dollar(line, garbage.new_env, 0);
			loop_create_maillons(garbage.line, &garbage, 0);
			cmd_to_path(garbage.maillons, garbage.new_env);
			find_all_heredoc(garbage.maillons);
			end_quote(&garbage);
			if (g_exit_code[1] != 7)
				pipex(garbage.maillons, &garbage.new_env, &garbage);
			free_garbage(&garbage);
		}
	}
	return (free_garbage_and_env(&garbage), 1);
}
