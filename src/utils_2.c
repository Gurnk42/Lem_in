/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 11:33:24 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/23 11:38:15 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*ft_search_for_node(char *name, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		if (ft_strcmp(((t_room *)(tmp->content))->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_print_all_paths(t_env *e)
{
	t_list	*tmp;

	tmp	= *(e->lst);
	while (tmp != NULL)
	{
		if (((t_room *)(tmp->content))->start_end == START)
		{
			((t_room *)(tmp->content))->checked = 1;
			e->len = ft_get_shortest_path_len(tmp, e);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_print_list_content(t_list *lst)
{
	int		i;
	t_list	*tmp;

	while (lst != NULL)
	{
		i = 0;
		ft_printf("\n\nROOM : '%s'\n", ((t_room *)(lst->content))->name);
		(((t_room *)(lst->content))->start_end == -1) ? ft_printf("END\n") : 0;
		(((t_room *)(lst->content))->start_end == 1) ? ft_printf("START\n") : 0;
		tmp = ((t_room *)(lst->content))->tunnels;
		while (tmp != NULL)
		{
			ft_printf("LINK[%d] : '%s'\n", i, (char *)tmp->content);
			tmp = tmp->next;
			i++;
		}
		lst = lst->next;
	}
}
