/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:27:55 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/22 18:28:52 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	second_if(char *line, int *i)
{
	(*i)++;
	if (line && line[(*i)] == '\0')
		return (-1);
	while (line && line[(*i)] != '\0' && line[(*i)] != '"')
		(*i)++;
	return (1);
}

int	skip_quote(char *line, int i)
{
	if (line && line[i] != '\0' && line[i + 1] != '\0'
		&& ((line[i] == '"' && line[i + 1] == '"')
			|| (line[i] == '\'' && line[i + 1] == '\'')))
		return (i + 1);
	while (line && line[i] != '\0' && line[i + 1] != '\0'
		&& ((line[i] == '"' && line[i + 1] != '"')
			|| (line[i] == '\'' && line[i + 1] != '\'')))
	{
		if (line[i] == '"' && line[i + 1] != '"')
			if (second_if(line, &i) == -1)
				return (-1);
		if (line && line[i] != '\0' && (line[i] == '\'' && line[i + 1] != '\''))
		{
			i++;
			if (line && line[i] == '\0')
				return (-1);
			while (line && line[i] != '\0' && line[i] != '\'')
				i++;
		}
		if (line && line[i] != '\0')
			i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		s1_len;
	int		s2_len;
	int		i;

	s1_len = ft_strlen ((char *)s1);
	s2_len = ft_strlen ((char *)s2);
	s = malloc ((s1_len + s2_len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	s1_len = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[s1_len])
	{
		s[i] = s2[s1_len];
		i++;
		s1_len++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strdup_const(const char *s, t_garbage *g)
{
	char	*s_copy;
	size_t	s_len;

	s_len = 0;
	if (s == NULL)
		return (NULL);
	s_len = ft_strlen_const(s);
	s_copy = malloc((s_len + 1) * sizeof(char));
	if (s_copy == NULL)
		return (free_garbage_env_exit(g, 1), NULL);
	s_len = 0;
	while (s[s_len])
	{
		s_copy[s_len] = s[s_len];
		s_len++;
	}
	s_copy[s_len] = '\0';
	return (s_copy);
}

int	check_dollar(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] != '\0')
	{
		if (line[i] == '$')
			return (0);
		i++;
	}
	return (1);
}
