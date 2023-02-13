/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:06:46 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/13 13:06:47 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* join et rajoute un \ entre path et add*/

char	*ft_strjoin_pipex(char *path, char *add)
{
	int		i;
	int		j;
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(add) + 2));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (path && path[i])
	{
		res[i] = path[i];
		i++;
	}
	res[i++] = '/';
	while (add && add[j])
		res[i++] = add[j++];
	res[i] = '\0';
	//free(path);
	return (res);
}
