/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 11:29:02 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/23 11:32:41 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_free_tunnels(t_list *lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = lst;
	while (tmp != NULL)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		ft_strdel(((char **)&(tmp2->content)));
		free(tmp2);
		tmp2 = NULL;
	}
}

void	ft_free_main_list(t_list **lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	while (tmp != NULL)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		ft_strdel(&(((t_room *)(tmp2->content))->name));
		ft_free_tunnels(((t_room *)(tmp2->content))->tunnels);
		ft_memdel((void **)&(tmp2->content));
		free(tmp2);
		tmp2 = NULL;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		ft_strdel(split + i);
		i++;
	}
}
