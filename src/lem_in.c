/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:05:08 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/20 20:02:16 by ebouther         ###   ########.fr       */
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

static int	ft_get_tunnel(t_list *tunnels, t_list **lst, t_list **next_rooms, char *name)
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
		if ((tmp = ft_search_for_node(((t_path *)(tunnels->content))->name, lst)) != NULL)//*lst;
		{
			if (((t_room *)(tmp->content))->checked == 0)
			{
				((t_room *)(tmp->content))->checked = 1;
				checked++;
				if (((t_room *)(tmp->content))->start_end == END)
				{
					/*path_tmp = (t_path *)(tunnels->content);
					while (path_tmp != NULL)
					{
						ft_printf("PATH : '%s'\n", path_tmp->name);
						path_tmp = path_tmp->previous;
					}*/
					return (1);
				}
				// ADD NEXT DISTANCE TUNNELS TO NEXT_ROOMS_2
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
								ft_lstnew((void *)path_tmp, sizeof(t_room *)));
						ft_printf("ROOM NAME : '%s'\n", (char *)tmp2->content);
						ft_printf("PREVIOUS : '%s'\n", ((t_path *)(path_tmp->previous))->name);
						ft_printf("2nd PREVIOUS : '%s'\n",
							(t_path *)((t_path *)(path_tmp->previous))->previous);
					}
					tmp2 = tmp2->next;
				}
				///////////////////////////////////////////
			}
		}
		tunnels = tunnels->next;
	}
	/*tmp2 = *next_rooms;
	while (tmp2 != NULL)
	{
		ft_printf("NEXT ROOM NAME : '%s'\n", (char *)tmp2->content);
		tmp2 = tmp2->next;
	}*/
	ft_printf("__________________________\n\n");
	if (checked > 0) // SHOULD SWITCH NEXT_ROOMS AND NEXT_ROOMS_2 and free NEXT_ROOMS_2
		return (0);
	return (-1);
}

static int	ft_get_shortest_path_len(t_list *node, t_list **lst, t_env *e)
{
	t_list	*tmp;
	t_list	*first_node;
	t_list	*next_rooms;
	t_list	*next_rooms_2;
	t_list	*all_depths;
	t_path	*path_tmp;
	int		ret;
	char	*current;
	int i;
	
	i = 1;
	(void)e;
	first_node = node;
	all_depths = NULL;
	next_rooms = NULL;
	next_rooms_2 = NULL;
	tmp = ((t_room *)(node->content))->tunnels;
	while (tmp != NULL)
	{
		if ((path_tmp = (t_path *)malloc(sizeof(t_path))) == NULL)
			ft_error_exit("Cannot allocate memory for path_tmp.\n");
			ft_printf("ADDED : '%s'\n", (char *)tmp->content);
			path_tmp->name = tmp->content;
			path_tmp->got_prev = 100000000;
			path_tmp->previous = malloc(sizeof(t_path *));
			ft_printf("ADDRESS : '%p'\n", path_tmp->previous);
			ft_printf("NAME ADDRESS : '%p'\n", path_tmp->name);
		ft_lstadd(&next_rooms,
				ft_lstnew((void *)path_tmp, sizeof(t_room *)));
		tmp = tmp->next;
	}

	if (DEBUG == 1)
	{
		tmp = next_rooms;
		while (tmp != NULL)
		{
			ft_printf("NAME ADRESS 2: '%p'\n",  ((t_path *)(tmp->content))->name);
			ft_printf("ROOM NAME : '%s'\n", ((t_path *)(tmp->content))->name);
			ft_printf("ADDRESS 2: '%p'\n", ((t_path *)(tmp->content))->previous);
			ft_printf("GOT PREVIOUS : '%d'\n", ((t_path *)(tmp->content))->got_prev);
			tmp = tmp->next;
		}
		ft_printf("___________________\n\n");
	}
	current = (char *)((t_room *)(node->content))->name;
	while ((ret = ft_get_tunnel(next_rooms, lst, &next_rooms_2, current)) != 1)
	{
		if (ret == 0)
		{
			if ((path_tmp = (t_path *)malloc(sizeof(t_path))) == NULL)
				ft_error_exit("Cannot allocate memory for path_tmp.\n");
			path_tmp->name = ((t_room *)(node->content))->name;
			ft_lstadd(&next_rooms, ft_lstnew((void *)
						path_tmp, sizeof(char *)));
			ft_lstadd(&all_depths, ft_lstnew((void *)
						next_rooms, sizeof(char *)));
			next_rooms = next_rooms_2;
		}
		else if (ret == -1)
			ft_error_exit("There's no path to the end.\n");
		i++;
	}
	ft_printf("LEN OF SHORTEST PATH : '%d'\n", i);
	return (i);
}

static void	ft_print_all_paths(t_list **lst, t_env *e)
{
	t_list	*tmp;
	int	len;

	tmp	= *lst;
	while (tmp != NULL)
	{
		if (((t_room *)(tmp->content))->start_end == START) // START FROM THE END
		{
			((t_room *)(tmp->content))->checked = 1;
			len = ft_get_shortest_path_len(tmp, lst, e);
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

static void	ft_get_rooms(int *start_end, char *line, t_list **lst, t_env *e)
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
	tmp->ants_there = 0;
	tmp->checked = 0;
	tmp->distance = -1;
	tmp->tunnels = NULL;
	if (*start_end == 1 || *start_end == -1)
	{
		(*start_end == 1) ? (e->start = ft_strdup(tmp->name)) : 
			(e->end = ft_strdup(tmp->name));
		tmp->start_end = *start_end;
		*start_end = 0;
	}
	ft_lstadd(lst, ft_lstnew((void *)tmp, sizeof(t_room)));
}

static void	ft_parse(t_list **lst, t_env *e)
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
					ft_get_rooms(&start_end, line, lst, e);
				else
					ft_link_rooms(line, lst);
			}
			i++;
		}
	}
}

int main(int argc, char **argv)
{
	t_list	*lst;
	t_env	env;

	(void)argc;
	(void)argv;
	if ((lst = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (0); //Should print error there.
	lst = NULL;
	ft_parse(&lst, &env);
	if (DEBUG == 1)
		ft_print_list_content(lst);
	ft_print_all_paths(&lst, &env);
	return (0);
}
