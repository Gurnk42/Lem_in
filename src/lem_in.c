/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:05:08 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/21 17:38:24 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*ft_search_for_node(char *name, t_list **lst)
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

static int	ft_get_tunnel(t_list *tunnels, t_list **next_rooms,
		char *name, t_env *e)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_path	*path_tmp;
	int		i;
	int		checked;

	i = 0;
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
				if (((t_room *)(tmp->content))->start_end == END)
				{
					path_tmp = (t_path *)(tunnels->content);
					while (path_tmp != NULL)
					{
						ft_lstadd(&(e->shortest_path),
							ft_lstnew((void *)path_tmp, sizeof(t_path)));
						path_tmp = path_tmp->previous;
					}
				/*ft_lstadd(&(e->shortest_path),
					ft_lstnew((void *)e->start, sizeof(char *)));*/
					return (1);
				}
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
		}
		tunnels = tunnels->next;
	}
	if (checked > 0)
		return (0);
	return (-1);
}

static int	ft_get_shortest_path_len(t_list *node, t_env *e)
{
	t_list	*tmp;
	t_list	*tunnels;
	t_list	*next_rooms;
	t_path	*path_tmp;
	int		ret;
	char	*current;
	int i;
	
	i = 1;
	tunnels = NULL;
	next_rooms = NULL;
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

static void	ft_print_all_paths(t_env *e)
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

static void	ft_print_list_content(t_list *lst)
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

static void	ft_link_rooms(char *line, t_list **lst)
{
	t_list	*begin;
	t_list	*tmp;
	char	**split;
	int		count;

	count = 0;
	begin = *lst;
	tmp = *lst;
	split = ft_strsplit(line, '-'); // Free dat shit later
	if (ft_strcmp(split[0], split[1]) == 0)
		ft_error_exit("Room is linked to itself.\n");
	if (ft_split_len(split) > 2)
		ft_error_exit("Bad format for room links.\n");
	while (tmp != NULL)
	{
		if (ft_strcmp(((t_room *)(tmp->content))->name, split[0]) == 0)
		{
			ft_lstadd(&(((t_room *)(tmp->content))->tunnels),
					ft_lstnew((void *)ft_strdup(split[1]), sizeof(char *)));
			count++;
		}
		else if (ft_strcmp(((t_room *)(tmp->content))->name, split[1]) == 0)
		{
			ft_lstadd(&(((t_room *)(tmp->content))->tunnels),
					ft_lstnew((void *)ft_strdup(split[0]), sizeof(char *)));
			count++;
		}
		tmp = tmp->next;
	}
	if (count != 2)
	{
		ft_printf("LINE : '%s'\n", line);
		ft_error_exit("Bad room name in room links.\n");
	}
}

static void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		ft_strdel(split + i);
		i++;
	}
}

static void	ft_get_rooms(int *start_end, char *line, t_env *e)
{
	t_room	*tmp;
	char	**split;

	(void)e;
	tmp = NULL;
	split = ft_strsplit(line, ' '); // Free dat shit later
	if ((tmp = (t_room *)malloc(sizeof(t_room))) == NULL)
		ft_error_exit("Cannot allocate list content\n");
	tmp->name = ft_strdup(split[0]);
	tmp->pos.x = ft_atoi_error_exit(split[1], "INT OVERFLOW. Exit.\n");
	tmp->pos.x = ft_atoi_error_exit(split[2], "INT OVERFLOW. Exit.\n");
	tmp->checked = 0;
	tmp->tunnels = NULL;
	if (*start_end == 1 || *start_end == -1)
	{
		(*start_end == 1) ? (e->start = ft_strdup(tmp->name)) : 
			(e->end = ft_strdup(tmp->name));
		tmp->start_end = *start_end;
		*start_end = 0;
	}
	ft_free_split(split);
	ft_lstadd(e->lst, ft_lstnew((void *)tmp, sizeof(t_room)));
}

static void	ft_parse(t_env *e)
{
	char	*line;
	int		i;
	int		start_end;

	i = 0;
	start_end = 0;
	while (get_next_line(0, &line))
	{
		if (ft_strncmp(line, "##", 2) == 0)
		{
			if (ft_strcmp(line, "##start") == 0)
				start_end = 1;
			else if (ft_strcmp(line, "##end") == 0)
				start_end = -1;
			else
				ft_error_exit("Bad line starting with \"##\"");
		}
		if (*line != '#')
		{
			if (i == 0)
				e->ants_nb = ft_atoi(line);
			else
			{
				if (ft_strchr(line, ' ') != NULL)
					ft_get_rooms(&start_end, line, e);
				else
					ft_link_rooms(line, e->lst);
			}
			i++;
		}
		ft_strdel(&line);
	}
}

static void	ft_free_tunnels(t_list *lst)
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

static void	ft_free_main_list(t_list **lst)
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

static void	ft_print_ants(t_env *e)
{
	int	i;
	int	n;
	t_list *tmp;

	i = 0;
	//ft_printf("LEN : '%d'\n", e->len);
	while (i < e->ants_nb)
	{
		tmp = e->shortest_path;
		n = 0;
		while (tmp != NULL && n <= i)
		{
			//while (n < i + 1)
			ft_printf("L%d-%s ", /*n++ +*/ 1, ((t_path *)(tmp->content))->name);
			tmp = tmp->next; 
		}
		ft_printf("\n");
		i++;
	}
}

int main(int argc, char **argv)
{
	t_env	env;

	(void)argc;
	(void)argv;
	if ((env.lst = (t_list **)malloc(sizeof(t_list *))) == NULL)
		return (0); //Should print error there.
	*(env.lst) = NULL;
	env.shortest_path = NULL;
	ft_parse(&env);
	if (DEBUG == 1)
		ft_print_list_content((*(env.lst)));
	ft_print_all_paths(&env);
	ft_free_main_list(env.lst);
	ft_print_ants(&env);
	return (0);
}
