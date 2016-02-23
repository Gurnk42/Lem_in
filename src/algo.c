/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 11:32:51 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/23 12:10:17 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void ft_get_tunnel_core_2(t_list *tunnels, t_list *tmp, t_list **next_rooms, t_path *path_tmp, char *name)
{
	t_list	*tmp2;

	tmp2 = ((t_room *)(tmp->content))->tunnels;
	while (tmp2 != NULL)
	{
		if (ft_strcmp((char *)tmp2->content, name) != 0)
		{
			if ((path_tmp = (t_path *)malloc(sizeof(t_path))) == NULL)
				ft_error_exit("Cannot allocate memory for path_tmp.\n");
			path_tmp->name = tmp2->content;
			path_tmp->previous = ((t_path *)(tunnels->content));
			ft_lstadd(next_rooms,
					ft_lstnew((void *)path_tmp, sizeof(t_path)));
		}
		tmp2 = tmp2->next;
	}
}

static int ft_get_tunnel_core(t_list *tunnels, t_list *tmp, t_list **next_rooms, char *name, t_env *e)
{
	t_path	*path_tmp;

	path_tmp = NULL;
	if (((t_room *)(tmp->content))->start_end == END)
	{
		path_tmp = (t_path *)(tunnels->content);
		while (path_tmp != NULL)
		{
			ft_lstadd(&(e->shortest_path),
				ft_lstnew((void *)path_tmp->name, sizeof(char *)));
			path_tmp = path_tmp->previous;
		}
		return (1);
	}
	ft_get_tunnel_core_2(tunnels, tmp, next_rooms, path_tmp, name);
	return (0);
}

int	ft_get_tunnel(t_list *tunnels, t_list **next_rooms,
		char *name, t_env *e)
{
	t_list	*tmp;
	int		checked;

	checked = 0;
	while (tunnels != NULL)
	{
		if ((tmp = ft_search_for_node(((t_path *)(tunnels->content))->name,
						e->lst)) != NULL)
		{
			if (((t_room *)(tmp->content))->checked == 0)
			{
				((t_room *)(tmp->content))->checked = 1;
				checked++;
				if (ft_get_tunnel_core(tunnels, tmp, next_rooms, name, e) == 1)
					return (1);
			}
		}
		tunnels = tunnels->next;
	}
	if (checked > 0)
		return (0);
	return (-1);
}


static int	ft_get_shortest_path_len_core(t_path *path_tmp, t_list *tunnels, t_list *node, t_env *e)
{
	char	*current;
	t_list	*next_rooms;
	int		ret;
	int i;

	i = 1;
	next_rooms = NULL;
	current = (char *)((t_room *)(node->content))->name;
	while ((ret = ft_get_tunnel(tunnels, &next_rooms, current, e)) != 1)
	{
		if (ret == 0)
		{
			if ((path_tmp = (t_path *)malloc(sizeof(t_path))) == NULL)
				ft_error_exit("Cannot allocate memory for path_tmp.\n");
			path_tmp->name = ((t_room *)(node->content))->name;
			ft_lstadd(&tunnels, ft_lstnew((void *)
						path_tmp, sizeof(t_path)));
			tunnels = next_rooms;
		}
		else if (ret == -1)
			ft_error_exit("There's no path to the end.\n");
		i++;
	}
	return (i);
}

int	ft_get_shortest_path_len(t_list *node, t_env *e)
{
	t_list	*tmp;
	t_list	*tunnels;
	t_path	*path_tmp;

	tunnels = NULL;
	tmp = ((t_room *)(node->content))->tunnels;
	while (tmp != NULL)
	{
		if ((path_tmp = (t_path *)malloc(sizeof(t_path))) == NULL)
			ft_error_exit("Cannot allocate memory for path_tmp.\n");
		path_tmp->name = (char *)tmp->content;
		path_tmp->previous = NULL;
		ft_lstadd(&tunnels,
				ft_lstnew((void *)path_tmp, sizeof(t_path)));
		tmp = tmp->next;
	}
	return (ft_get_shortest_path_len_core(path_tmp, tunnels, node, e));
}

