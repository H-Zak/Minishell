/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_commande.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:37:34 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 17:46:50 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*
* print la commande et ces argument si il y en a
*
*   a changer et a envoyer sa dans la structure maillon dans commande
*	et arg sous forme de tab
*
*/
// si l' prev est pas un < ou << ou > ou >> (pour le premier if)
// si *lst differend de > >> < << (pour le deuxieme if)
char	*find_command(t_split_elem *lst)
{
	t_split_elem	*prev;

	prev = lst;
	while (lst)
	{
		if (!(ft_strcmp(prev->arg, "<") || ft_strcmp(prev->arg, "<<")
				|| ft_strcmp(prev->arg, ">") || ft_strcmp(prev->arg, ">>")))
			if (!(ft_strcmp((lst)->arg, "<") || ft_strcmp((lst)->arg, "<<")
					|| ft_strcmp((lst)->arg, ">")
					|| ft_strcmp((lst)->arg, ">>")))
				return (ft_strdup((lst)->arg));
		prev = lst;
		lst = (lst)->next;
	}
	return (NULL);
}

// si l' prev est pas un < ou << ou > ou >>(pour le premier if)
// si *lst differend de > >> < << (pour le deuxieme if)
int	count_arg(t_split_elem *lst)
{
	t_split_elem	*prev;
	int				i;

	i = 0;
	prev = lst;
	while (lst)
	{
		if (!(ft_strcmp(prev->arg, "<") || ft_strcmp(prev->arg, "<<")
				|| ft_strcmp(prev->arg, ">") || ft_strcmp(prev->arg, ">>")))
			if (!(ft_strcmp((lst)->arg, "<") || ft_strcmp((lst)->arg, "<<")
					|| ft_strcmp((lst)->arg, ">")
					|| ft_strcmp((lst)->arg, ">>")))
				i++;
		prev = lst;
		lst = (lst)->next;
	}
	return (i);
}

int	find_argument_loop(t_split_elem *lst)
{
	return ((!(ft_strcmp((lst)->arg, "<") || ft_strcmp((lst)->arg, "<<")
				|| ft_strcmp((lst)->arg, ">") || ft_strcmp((lst)->arg, ">>"))));
}

// si l' prev est pas un < ou << ou > ou >> (pour le premier if)
// si *lst differend de > >> < << (pour le deuxieme if)
char	**find_argument(t_split_elem *lst, t_garbage *g, int i, int len)
{
	t_split_elem	*prev;
	char			**r;

	r = malloc(sizeof(char *) * (len + 1));
	if (!r)
		free_garbage_env_exit(g, 1);
	prev = lst;
	while (lst)
	{
		if (!(ft_strcmp(prev->arg, "<") || ft_strcmp(prev->arg, "<<")
				|| ft_strcmp(prev->arg, ">") || ft_strcmp(prev->arg, ">>")))
		{
			if (find_argument_loop(lst))
			{
				r[i] = ft_strdup(lst->arg);
				if (!r[i])
					return (ft_free_tab(r), free_garbage_env_exit(g, 1), NULL);
				i++;
			}
		}
		prev = lst;
		lst = (lst)->next;
	}
	r[i] = 0;
	return (r);
}
