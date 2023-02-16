/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:24:35 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/13 11:24:36 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split_elem	*ft_split_list(char *str, char *sep)
{
	int				i;
	t_split_elem	*lst;
	t_split_elem	*elem;
	char			*res;
	char			quote;
	int count;

	i = 0;
	lst = NULL;
	count = count_words2(str, sep);
	while (count--)
	{
		res = ft_strtab(str, i, sep);
		elem = create_split_elem(res);
		add_end_split_elem(&lst, elem);
		i++;
	}
	return (lst);
}